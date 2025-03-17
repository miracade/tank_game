#pragma once

#include <array>
#include <cstdint>

#include "persistent.hpp"
#include "sprites.hpp"
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

struct Rgbx {
  uint8_t x = 0;
  uint8_t b;
  uint8_t g;
  uint8_t r;

  Rgbx() = default;
  Rgbx(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

class IO {
 public:
  static constexpr Vec2i kScreenSize{320, 240};
  static constexpr int kScreenScale = 4;

  IO();

  void Update();
  void FinishFrame();

  // input functions
  bool IsKeyHeld(Key key) const;
  bool IsKeyJustPressed(Key key) const;
  bool IsKeyJustReleased(Key key) const;
  bool IsAnyKeyPressed() const;

  // drawing functions
  void DrawPixel(Vec2i xy, Rgbx px);
  void DrawSprite(Vec2i xy, const Sprites::Sprite& spr);

  /**
   * @brief Draws a rectangular portion of a sprite.
   * @param dst_xy screen coordinates
   * @param spr sprite to draw
   * @param src_xy top-left corner of the drawn portion of the sprite
   * @param src_size size of the drawn portion of the sprite
   */
  void DrawPartialSprite(Vec2i dst_xy, const Sprites::Sprite& spr, Vec2i src_xy,
                         Vec2i src_size);
  void Fill(Rgbx px);

  // utility functions
  int GetFrameNumber() const;
  uint32_t Random() const;

  ~IO();

  // save file
  PersistentData save_file{"save.json"};

 private:
  std::array<bool, ToUnderlying(Key::kCount)> pressed_keys_ = {};
  std::array<bool, ToUnderlying(Key::kCount)> pressed_keys_last_frame_ = {};

  int frame_number_ = 0;
};

inline IO io;