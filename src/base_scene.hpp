#pragma once

#include <memory>

class BaseScene {
 public:
  BaseScene() = default;
  virtual std::unique_ptr<BaseScene> Update() { return nullptr; };
  virtual void Render() {};
  virtual ~BaseScene() noexcept = default;
};