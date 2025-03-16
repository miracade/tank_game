#pragma once

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <fstream>

static std::ofstream log_file("latest.log");

#define LOG_SRC fmt::format("{}:{}", __FILE__, __LINE__)
#define LOG_DEBUG(...)                                                \
  log_file << fmt::format("        {:20.20} {} [{}]\n", __FUNCTION__, \
                          fmt::format(__VA_ARGS__), LOG_SRC)
#define LOG_ERROR(...)                                               \
  do {                                                               \
    auto s = fmt::format("[ERROR] {:20.20} {} [{}]\n", __FUNCTION__, \
                         fmt::format(__VA_ARGS__), LOG_SRC);         \
    log_file << s;                                                   \
    std::clog << s;                                                  \
  } while (0)
