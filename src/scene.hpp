#pragma once

class Scene {
 public:
  Scene() = default;
  virtual void Update() {};
  virtual void Render() {};
  virtual ~Scene() = default;
};