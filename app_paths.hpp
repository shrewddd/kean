#pragma once
#include <filesystem>

struct AppPaths {
  std::filesystem::path config_directory;
  std::filesystem::path data_directory;

  [[nodiscard]] std::filesystem::path config_file() const {
    return config_directory / "init.lua";
  }

  [[nodiscard]] std::filesystem::path database_file() const {
    return data_directory / "db.sqlite3";
  }
};

[[nodiscard]] AppPaths resolve_app_paths();
