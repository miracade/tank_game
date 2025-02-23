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
    io.Fill({0, 0, 64});
    io.DrawSprite(
        {static_cast<int>((io.GetFrameNumber() + io.Random() % 32) % 320 - 32),
         static_cast<int>((io.GetFrameNumber() + io.Random() % 32) % 240 - 32)},
        Sprites::MiniThinker);
    io.RenderAndWait();
  }
}