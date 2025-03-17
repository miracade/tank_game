#pragma once

#include <fmt/core.h>

#include <array>
#include <initializer_list>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

void print_zigzag(const std::string& str);

struct Vec2i {
  int x;
  int y;

  friend bool operator==(const Vec2i& lhs, const Vec2i& rhs) = default;
  friend Vec2i operator-(const Vec2i& lhs, const Vec2i& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
  }
  inline Vec2i mul(const Vec2i& other) const {
    return {x * other.x, y * other.y};
  }
};

std::string format_as(const Vec2i& v);

template <typename EnumType>
constexpr std::underlying_type_t<EnumType> ToUnderlying(EnumType e) {
  return static_cast<std::underlying_type_t<EnumType>>(e);
}

/**
 * @brief Mapping from an enum type to a value
 * @tparam EnumType
 * @tparam MappedType
 */
template <typename EnumType, typename MappedType>
class EnumMap {
 public:
  constexpr EnumMap(
      std::initializer_list<std::pair<EnumType, MappedType>> pairs)
      : data_{} {
    for (const auto& [key, value] : pairs) {
      data_[ToUnderlying(key)] = value;
    }
  }

  constexpr MappedType operator[](EnumType key) const {
    return data_[ToUnderlying(key)];
  }

 private:
  std::array<MappedType, ToUnderlying(EnumType::kCount)> data_;
};
