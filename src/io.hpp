#pragma once

#include <array>

#include "util.hpp"

enum class Key {
  kUp,
  kDown,
  kLeft,
  kRight,
  kQuit,
  kCount,
};

class IO {
 public:
  IO();
  void Update();
  void Wait();
  ~IO();

 private:
  std::array<bool, ToUnderlying(Key::kCount)> pressed_keys_ = {};
};