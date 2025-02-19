
#include <iostream>
#include <thread>

#include "io.hpp"
#include "util.hpp"

int main() {
  print_zigzag("hoppo bounce!!");
  IO io;
  while (true) {
    io.Update();
    io.Wait();
  }
}