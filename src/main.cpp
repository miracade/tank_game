#include <iostream>
#include <thread>

#include "io.hpp"
#include "sample_scene.hpp"
#include "scene.hpp"
#include "sprites.hpp"
#include "util.hpp"

int main() {
  std::unique_ptr<Scene> scene = std::make_unique<SampleScene>();
  while (true) {
    io.Update();
    if (io.IsKeyJustPressed(Key::kQuit)) {
      break;
    }
    if (io.IsKeyJustPressed(Key::kConfirm)) {
      scene = std::make_unique<SampleScene>();
    }
    scene->Update();
    scene->Render();
    io.FinishFrame();
  }
}