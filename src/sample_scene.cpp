#include "sample_scene.hpp"

#include "io.hpp"
#include "sprites.hpp"

std::unique_ptr<BaseScene> SampleScene::Update() {
  ++age_;
  if (io.IsKeyHeld(Key::kRight)) {
    pos_.x += 1;
  }
  if (io.IsKeyHeld(Key::kLeft)) {
    pos_.x -= 1;
  }
  if (io.IsKeyHeld(Key::kDown)) {
    pos_.y += 1;
  }
  if (io.IsKeyHeld(Key::kUp)) {
    pos_.y -= 1;
  }

  if (io.IsKeyJustPressed(Key::kConfirm)) {
    return std::make_unique<SampleScene>();
  }
  return nullptr;
}

void SampleScene::Render() {
  io.Fill({128, 128, 64});
  // io.DrawSprite({32, 32}, Sprites::Rgb);
  // io.DrawSprite(
  //     {static_cast<int>(age_ % 320 - 32), static_cast<int>(age_ % 240 - 32)},
  //     Sprites::MiniThinker);
  io.DrawPartialSprite({0, 0}, Sprites::Tankgame, pos_, {32, 32});
  io.DrawPartialSprite({0, 0}, Sprites::Tankgame, pos_, {64, 64});
  // io.DrawSprite({16, 128}, Sprites::TankWorkShop);
}
