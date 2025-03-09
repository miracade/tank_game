#pragma once

#include <fstream>
#include <string>

#include "io.hpp"
#include "json.hpp"

class PersistentData {
 public:
  PersistentData(const std::string& fp) : file_path_{fp} {
    std::ifstream file{file_path_};
    file >> data_;
  }

  template <typename T>
  void Set(const std::string& key, const T& value) {
    data_[key] = value;
    std::ofstream file{file_path_};
    file << data_.dump(2);
  }

  template <typename T>
  T Get(const std::string& key) {
    return data_[key].get<T>();
  }

  void Erase(const std::string& key) {
    data_.erase(key);
    std::ofstream file{file_path_};
    file << data_.dump(2);
  }

 private:
  const std::string file_path_;
  nlohmann::json data_ = {};
};
