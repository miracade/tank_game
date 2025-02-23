#include "sample_scene.hpp"

#include "io.hpp"
#include "sprites.hpp"

void SampleScene::Update() { ++age_; }

void SampleScene::Render() {
  io.Fill({0, 0, 64});
  io.DrawSprite({32, 32}, Sprites::Rgb);
  io.DrawSprite(
      {static_cast<int>(age_ % 320 - 32), static_cast<int>(age_ % 240 - 32)},
      Sprites::MiniThinker);
}
