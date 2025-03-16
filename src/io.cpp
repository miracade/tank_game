#include "io.hpp"

#include <algorithm>
#include <iostream>
#include <random>

#include "logging.hpp"
#include "util.hpp"

#if NSPIRE == 1
IO::IO() {}

IO::~IO() {}

#else

#include <SDL3/SDL.h>

#include <chrono>
#include <thread>

namespace {
IO* io_ptr = nullptr;
static SDL_Window* win = nullptr;
static SDL_Renderer* rend = nullptr;
static SDL_Texture* tex = nullptr;
static Rgbx* screen_buffer = nullptr;
static int pitch = 0;
}  // namespace

IO::IO() {
  // only one instance of IO is allowed
  if (io_ptr) {
    throw std::runtime_error("IO instance already exists");
  }
  io_ptr = this;

  // initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG_ERROR("SDL_Init Error: {}", SDL_GetError());
  }

  win = SDL_CreateWindow("Tank Game", kScreenSize.x * kScreenScale,
                         kScreenSize.y * kScreenScale, 0);
  if (!win) {
    LOG_ERROR("SDL_CreateWindow Error: {}", SDL_GetError());
  }

  rend = SDL_CreateRenderer(win, NULL);
  if (!rend) {
    LOG_ERROR("SDL_CreateRenderer Error: {}", SDL_GetError());
  }

  tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBX8888,
                          SDL_TEXTUREACCESS_STREAMING, kScreenSize.x,
                          kScreenSize.y);
  if (!tex) {
    LOG_ERROR("SDL_CreateTexture Error: {}", SDL_GetError());
  }
  SDL_SetTextureScaleMode(tex, SDL_ScaleMode::SDL_SCALEMODE_NEAREST);
  SDL_LockTexture(tex, NULL, (void**)(&screen_buffer), &pitch);
}

void IO::Update() {
  ++frame_number_;
  std::ranges::copy(pressed_keys_, pressed_keys_last_frame_.begin());

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        LOG_DEBUG("SDL_QUIT event");
        std::terminate();
        break;
      case SDL_EVENT_KEY_DOWN:
      case SDL_EVENT_KEY_UP:
        switch (event.key.key) {
          case SDLK_UP:
            pressed_keys_[ToUnderlying(Key::kUp)] = event.key.down;
            break;
          case SDLK_DOWN:
            pressed_keys_[ToUnderlying(Key::kDown)] = event.key.down;
            break;
          case SDLK_LEFT:
            pressed_keys_[ToUnderlying(Key::kLeft)] = event.key.down;
            break;
          case SDLK_RIGHT:
            pressed_keys_[ToUnderlying(Key::kRight)] = event.key.down;
            break;
          case SDLK_Q:
            pressed_keys_[ToUnderlying(Key::kQuit)] = event.key.down;
            break;
          case SDLK_Z:
            pressed_keys_[ToUnderlying(Key::kConfirm)] = event.key.down;
            break;
          case SDLK_X:
            pressed_keys_[ToUnderlying(Key::kCancel)] = event.key.down;
            break;
          case SDLK_C:
            pressed_keys_[ToUnderlying(Key::kMine)] = event.key.down;
            break;
          case SDLK_V:
            pressed_keys_[ToUnderlying(Key::kUse)] = event.key.down;
            break;
          default:
            LOG_DEBUG("Unknown key: {}", event.key.key);
            break;
        }
    }
  }
}

void IO::FinishFrame() {
  static constexpr SDL_FRect src{0, 0, kScreenSize.x, kScreenSize.y};
  static constexpr SDL_FRect dst{0, 0, kScreenSize.x * kScreenScale,
                                 kScreenSize.y * kScreenScale};

  // render to screen
  SDL_UnlockTexture(tex);
  SDL_RenderTexture(rend, tex, &src, &dst);
  SDL_RenderPresent(rend);
  SDL_LockTexture(tex, NULL, (void**)(&screen_buffer), &pitch);

  using namespace std::chrono;

  // wait for next frame
  static auto last_frame_time = system_clock::now();
  if (system_clock::now() - last_frame_time > microseconds(16'600)) {
    LOG_DEBUG("Frame took too long: {}us",
              duration_cast<microseconds>(system_clock::now() - last_frame_time)
                  .count());
  }
  std::this_thread::sleep_until(last_frame_time + microseconds(16'600));
  last_frame_time = system_clock::now();
}

bool IO::IsKeyHeld(Key key) const { return pressed_keys_[ToUnderlying(key)]; }

bool IO::IsKeyJustPressed(Key key) const {
  return pressed_keys_[ToUnderlying(key)] &&
         !pressed_keys_last_frame_[ToUnderlying(key)];
}

bool IO::IsKeyJustReleased(Key key) const {
  return !pressed_keys_[ToUnderlying(key)] &&
         pressed_keys_last_frame_[ToUnderlying(key)];
}

bool IO::IsAnyKeyPressed() const {
  return std::ranges::any_of(pressed_keys_, [](bool key) { return key; });
}

void IO::DrawPixel(Vec2i xy, Rgbx px) {
  // if (xy.x < 0 || xy.x >= kScreenSize.x || xy.y < 0 || xy.y >= kScreenSize.y)
  // {
  //   return;
  // }
  screen_buffer[xy.y * kScreenSize.x + xy.x] = px;
}

void IO::DrawSprite(Vec2i xy, const Sprites::Sprite& spr) {
  DrawPartialSprite(xy, spr, {0, 0}, spr.size);
}

void IO::DrawPartialSprite(Vec2i dst_topleft, const Sprites::Sprite& spr,
                           Vec2i src_topleft, Vec2i src_size) {
  if (src_topleft.x < 0 || src_topleft.x + src_size.x > spr.size.x ||
      src_topleft.y < 0 || src_topleft.y + src_size.y > spr.size.y) {
    LOG_ERROR("Refusing to draw tl={} sz={} of sprite {:?} (size={})",
              src_topleft, src_size, spr.name, spr.size);
    return;
  }
  for (int y = 0; y < src_size.y; ++y) {
    for (int x = 0; x < src_size.x; ++x) {
      auto src_y = src_topleft.y + y;
      auto src_x = src_topleft.x + x;
      const uint8_t* px = &spr.data[(src_y * spr.size.x + src_x) * 4];
      if (px[0] != 255) {
        continue;
      }
      DrawPixel({dst_topleft.x + x, dst_topleft.y + y}, {px[3], px[2], px[1]});
    }
  }
}

void IO::Fill(Rgbx px) {
  for (int y = 0; y < kScreenSize.y; ++y) {
    for (int x = 0; x < kScreenSize.x; ++x) {
      DrawPixel({x, y}, px);
    }
  }
}

int IO::GetFrameNumber() const { return frame_number_; }

uint32_t IO::Random() const {
  static std::mt19937 rng;
  return rng();
}

IO::~IO() {
  SDL_DestroyWindow(win);
  SDL_Quit();
}
#endif
