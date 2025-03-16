#pragma once

#include "scene.hpp"
#include "util.hpp"

class SampleScene : public Scene {
 public:
  SampleScene() = default;
  void Update() override;
  void Render() override;
  ~SampleScene() noexcept override = default;

 private:
  int age_ = 0;
  Vec2i pos_{0, 0};
};