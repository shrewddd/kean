#pragma once
#include <filesystem>
#include <string>

struct Config {
  std::string theme {"dark"};
};

[[nodiscard]] Config load_config(std::filesystem::path config_file);
