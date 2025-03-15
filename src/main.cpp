#include <iostream>
#include <thread>

#include "io.hpp"
#include "sample_scene.hpp"
#include "scene.hpp"
#include "sprites.hpp"
#include "util.hpp"

int main() {
  std::unique_ptr<Scene> scene = std::make_unique<SampleScene>();
  io.save_file.Set("name", "John Doe");
  io.save_file.Set("age", 0);
  while (true) {
    io.Update();
    if (io.IsKeyJustPressed(Key::kQuit)) {
      break;
    }
    if (io.IsKeyJustPressed(Key::kConfirm)) {
      scene = std::make_unique<SampleScene>();
    }
    io.save_file.Set("age", io.save_file.Get<int>("age") + 1);
    scene->Update();
    scene->Render();
    io.FinishFrame();
  }
}