#include <filesystem>
#include "config.hpp"
#include <iostream>
#include <system_error>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

Config load_config(std::filesystem::path config_file) {
  Config config {};

  std::error_code error;
  const bool exists { std::filesystem::exists(config_file, error) };

  if (error) {
    std::cerr << "kean: failed to inspect config file '"
              << config_file << "': " << error.message()
              << "; using defaults\n";
    return config;
  }

  if (!exists) {
    return config;
  }

  const bool is_regular_file { std::filesystem::is_regular_file(config_file, error) };

  if (error) {
    std::cerr << "kean: failed to inspect config file type '"
              << config_file << "': " << error.message()
              << "; using defaults\n";
    return config;
  }

  if (!is_regular_file) {
    std::cerr << "kean: config path is not a regular file: '"
              << config_file << "'; using defaults\n";
    return config;
  }

  sol::state lua;
  lua.script_file(config_file);
  std::string theme = lua["config"]["ui"]["theme"];
  config.theme = theme;

  return config;
}
