#pragma once

#include "base_scene.hpp"
#include "util.hpp"

class SampleScene : public BaseScene {
 public:
  SampleScene() = default;
  std::unique_ptr<BaseScene> Update() override;
  void Render() override;
  ~SampleScene() noexcept override = default;

 private:
  int age_ = 0;
  Vec2i pos_{0, 0};
};