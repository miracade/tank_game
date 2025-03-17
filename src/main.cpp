#include <iostream>
#include <thread>

#include "base_scene.hpp"
#include "io.hpp"
#include "logging.hpp"
#include "sample_scene.hpp"
#include "sprites.hpp"
#include "util.hpp"
#include "world_scene.hpp"

int main() {
  LOG_DEBUG("Game started");

  std::unique_ptr<BaseScene> scene = std::make_unique<WorldScene>();
  while (true) {
    io.Update();
    if (io.IsKeyJustPressed(Key::kQuit)) {
      break;
    }
    auto next_scene = scene->Update();
    scene->Render();
    io.FinishFrame();
    if (next_scene) {
      scene = std::move(next_scene);
    }
  }
}