
#include <iostream>
#include <thread>

#include "io.hpp"
#include "util.hpp"

int main() {
  IO io;
  while (true) {
    io.Update();
    io.Wait();
  }
}