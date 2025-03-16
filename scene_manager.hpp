#include <memory>

#include "scene.hpp"

class SceneManager {
 public:
  SceneManager(std::unique_ptr<BaseScene> s) : active_scene{std::move(s)} {};

  std::unique_ptr<BaseScene> active_scene;
};