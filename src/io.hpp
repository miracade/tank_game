#pragma once

#include <array>

#include "util.hpp"

enum class Key {
  kUp,
  kDown,
  kLeft,
  kRight,
  kQuit,
  kConfirm,
  kCancel,
  kMine,
  kUse,
  kCount
};

class IO {
 public:
  IO();

  void Update();
  void WaitUntilNextFrame();

  bool IsKeyHeld(Key key) const;
  bool IsKeyJustPressed(Key key) const;
  bool IsKeyJustReleased(Key key) const;

  bool IsAnyKeyPressed() const;

  ~IO();

 private:
  std::array<bool, ToUnderlying(Key::kCount)> pressed_keys_ = {};
  std::array<bool, ToUnderlying(Key::kCount)> pressed_keys_last_frame_ = {};
};