#pragma once

#include "base_scene.hpp"
#include "util.hpp"
#include "tile.hpp"

class WorldScene : public BaseScene {
 public:
  WorldScene();
  std::unique_ptr<BaseScene> Update() override;
  void Render() override;
  ~WorldScene() noexcept override = default;

  static constexpr Vec2i kWorldSize{16, 16};

 private:
  std::array<Tile, kWorldSize.x * kWorldSize.y> world_{};
  Vec2i camera_pos_{0, 0};
  int age_ = 0;
};