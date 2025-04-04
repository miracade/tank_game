#include "world_scene.hpp"

#include <algorithm>

#include "io.hpp"
#include "logging.hpp"
#include "sprites.hpp"

WorldScene::WorldScene() {
  for (auto& tile : world_) {
    tile.tile_type = TileType(io.Random() % ToUnderlying(TileType::kCount));
    if (tile.tile_type != TileType::kNone) {
      tile.loot_type = LootType(io.Random() % ToUnderlying(LootType::kCount));
    }
  }
}

std::unique_ptr<BaseScene> WorldScene::Update() {
  ++age_;
  if (io.IsKeyHeld(Key::kRight)) {
    camera_pos_.x += 3;
  } if (io.IsKeyHeld(Key::kLeft)) {
    camera_pos_.x -= 3;
  } if (io.IsKeyHeld(Key::kDown)) {
    camera_pos_.y += 3;
  } if (io.IsKeyHeld(Key::kUp)) {
    camera_pos_.y -= 3;
  }
  // if (camera_pos_.x >= kTileSize.x) {
  //   camera_pos_.x -= kTileSize.x;
  //   for (int row = 0; row < kWorldSize.y; ++row) {
  //     std::rotate(world_.begin() + row * kWorldSize.x,
  //                 world_.begin() + row * kWorldSize.x + 1,
  //                 world_.begin() + (row + 1) * kWorldSize.x);
  //   }
  // }
  return nullptr;
}

void WorldScene::Render() {
  io.Fill({40, 40, 40});
  for (int y = 0; y < kWorldSize.y; ++y) {
    for (int x = 0; x < kWorldSize.x; ++x) {
      const auto& tile = world_[y * kWorldSize.x + x];
      if (tile.tile_type != TileType::kNone) {
        io.DrawPartialSprite(
            Vec2i{x * kTileSize.x, y * kTileSize.y} - camera_pos_,
            Sprites::Tileset,
            kTileTypeAttributes[tile.tile_type].sprite_offset.mul(kTileSize),
            kTileSize);
      }
      if (tile.loot_type != LootType::kNone) {
        io.DrawPartialSprite(
            Vec2i{x * kTileSize.x, y * kTileSize.y} - camera_pos_,
            Sprites::Tileset,
            kLootTypeAttributes[tile.loot_type].sprite_offset.mul(kTileSize),
            kTileSize);
      }
    }
  }
}