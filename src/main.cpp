#include <iostream>
#include <thread>

#include "io.hpp"
#include "sprites.hpp"
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
        io.DrawPixel({x, y},
                     {static_cast<uint8_t>(x), 255, static_cast<uint8_t>(y)});
      }
    }
    io.DrawSprite({0, 0}, Sprites::Test2);
    io.RenderAndWait();
  }
}