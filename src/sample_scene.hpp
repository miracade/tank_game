#pragma once

#include "scene.hpp"

class SampleScene : public Scene {
 public:
  SampleScene() = default;
  void Update() override;
  void Render() override;
  ~SampleScene() override = default;

 private:
  int age_ = 0;
};