#include "io.hpp"

#include <algorithm>
#include <iostream>
#include <random>

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
  std::clog << "SDL version: " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION
            << "." << SDL_MICRO_VERSION << std::endl;
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::clog << "SDL_Init Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL_Init Error");
  }

  win = SDL_CreateWindow("Tank Game", kScreenSize.x * kScreenScale,
                         kScreenSize.y * kScreenScale, 0);
  if (!win) {
    std::clog << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL_CreateWindow Error");
  }

  rend = SDL_CreateRenderer(win, NULL);
  if (!rend) {
    std::clog << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL_CreateRenderer Error");
  }

  tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBX8888,
                          SDL_TEXTUREACCESS_STREAMING, kScreenSize.x,
                          kScreenSize.y);
  if (!tex) {
    std::clog << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL_CreateTexture Error");
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
        std::clog << "Quit" << std::endl;
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
            break;
        }
    }
  }

  if (IsAnyKeyPressed()) {
    std::clog << "Update" << std::endl;
    for (bool key : pressed_keys_) {
      std::clog << key << " ";
    }
    std::clog << std::endl;
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

  // wait for next frame (and log frame time)
  static auto last_frame_time = std::chrono::high_resolution_clock::now();
  std::clog << "Frame time: "
            << std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now() - last_frame_time)
                   .count()
            << " us" << std::endl;
  std::this_thread::sleep_until(last_frame_time +
                                std::chrono::microseconds(16'600));
  last_frame_time = std::chrono::high_resolution_clock::now();
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
  if (xy.x < 0 || xy.x >= kScreenSize.x || xy.y < 0 || xy.y >= kScreenSize.y) {
    return;
  }
  screen_buffer[xy.y * kScreenSize.x + xy.x] = px;
}

void IO::DrawSprite(Vec2i xy, const Sprites::Sprite& spr) {
  for (int y = 0; y < spr.size.y; ++y) {
    for (int x = 0; x < spr.size.x; ++x) {
      if (spr.data[(y * spr.size.x + x) * 4] != 255) {
        continue;
      }
      DrawPixel({xy.x + x, xy.y + y}, {spr.data[(y * spr.size.x + x) * 4 + 3],
                                       spr.data[(y * spr.size.x + x) * 4 + 2],
                                       spr.data[(y * spr.size.x + x) * 4 + 1]});
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
