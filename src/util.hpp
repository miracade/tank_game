#pragma once

#include <iostream>
#include <string>
#include <type_traits>

void print_zigzag(const std::string& str);

struct Vec2i {
  int x;
  int y;
};

template <typename EnumType>
constexpr std::underlying_type_t<EnumType> ToUnderlying(EnumType e) {
  return static_cast<std::underlying_type_t<EnumType>>(e);
}