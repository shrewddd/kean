#include <filesystem>
#define SOL_ALL_SAFETIES_ON 1
#include "config.hpp"
#include <sol/sol.hpp>

Config load_config(std::filesystem::path config_file) {
  Config config {};

  sol::state lua;
  lua.script_file("lua/default_config.lua");

  std::string theme = lua["config"]["ui"]["theme"];
  std::cout << theme << std::endl;
  config.theme = theme;

  lua.script_file(config_file);
  theme = lua["config"]["ui"]["theme"];
  std::cout << theme << std::endl;
  config.theme = theme;

  return config;
}
