#include "io.hpp"

#include <iostream>

#include "util.hpp"

#if NSPIRE == 1
IO::IO() {}

IO::~IO() {}

#else

#include <SDL3/SDL.h>

#include <chrono>
#include <thread>

static SDL_Window* win = nullptr;

IO::IO() {
  std::clog << "SDL version: " << SDL_MAJOR_VERSION << "." << SDL_MINOR_VERSION
            << "." << SDL_MICRO_VERSION << std::endl;
  print_zigzag("Lithium World");
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::clog << "SDL_Init Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL_Init Error");
  }

  std::clog << "Hello, Windows!" << std::endl;

  win = SDL_CreateWindow("Tank Game", 320, 240, 0);
  if (!win) {
    std::clog << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL_CreateWindow Error");
  }
}

void IO::Update() {
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
            pressed_keys_[static_cast<size_t>(Key::kUp)] = event.key.down;
            break;
          case SDLK_DOWN:
            pressed_keys_[static_cast<size_t>(Key::kDown)] = event.key.down;
            break;
          case SDLK_LEFT:
            pressed_keys_[static_cast<size_t>(Key::kLeft)] = event.key.down;
            break;
          case SDLK_RIGHT:
            pressed_keys_[static_cast<size_t>(Key::kRight)] = event.key.down;
            break;
          case SDLK_Q:
            pressed_keys_[static_cast<size_t>(Key::kQuit)] = event.key.down;
            break;
          default:
            break;
        }
    }
  }
  std::clog << "Update" << std::endl;
  for (bool key : pressed_keys_) {
    std::clog << key << " ";
  }
  std::clog << std::endl;
}

void IO::Wait() {
  static auto last_frame_time = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_until(last_frame_time +
                                std::chrono::microseconds(500'000));
  last_frame_time = std::chrono::high_resolution_clock::now();
}

IO::~IO() {
  SDL_DestroyWindow(win);
  SDL_Quit();
}
#endif
