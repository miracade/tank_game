#pragma once

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <fstream>
#include <ostream>

static std::ofstream log_file("latest.log");

#define LOG_SRC fmt::format("{}:{}", __FILE__, __LINE__)
#define LOG_DEBUG(...)                                                \
do {                                                               \
  auto s = fmt::format("[DEBUG] {:20.20} {} [{}]\n", __FUNCTION__, \
                       fmt::format(__VA_ARGS__), LOG_SRC);         \
  log_file << s;                                                   \
  std::clog << s;                                                  \
} while (0)

#define LOG_ERROR(...)                                               \
  do {                                                               \
    auto s = fmt::format("[ERROR] {:20.20} {} [{}]\n", __FUNCTION__, \
                         fmt::format(__VA_ARGS__), LOG_SRC);         \
    log_file << s;                                                   \
    std::clog << s;                                                  \
  } while (0)
