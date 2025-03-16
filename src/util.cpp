#include "util.hpp"

void print_zigzag(const std::string& str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (i % 2 == 0) {
      std::cout << str[i];
    } else {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
  for (size_t i = 0; i < str.size(); ++i) {
    if (i % 2 == 0) {
      std::cout << " ";
    } else {
      std::cout << str[i];
    }
  }
  std::cout << std::endl;
}

std::string format_as(const Vec2i& v)
{ return fmt::format("({}, {})", v.x, v.y); }