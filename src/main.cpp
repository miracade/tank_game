
#include <iostream>
#include <thread>

#include "io.hpp"
#include "util.hpp"

int main() {
  print_zigzag("hoppo bounce!!");
  while (true) {
    io.Update();
    if (io.IsKeyJustPressed(Key::kQuit)) {
      break;
    }
    for (int y = 0; y < io.kScreenSize.y; ++y) {
      for (int x = 0; x < io.kScreenSize.x; ++x) {
        io.DrawPixel({x, y}, {x, 255, y});
      }
    }
    io.RenderAndWait();
  }
}