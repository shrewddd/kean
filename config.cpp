#define SOL_ALL_SAFETIES_ON 1
#include "config.hpp"
#include <sol/sol.hpp>

void load_config(Config& config) {
  sol::state lua;
  lua.script_file("lua/default_config.lua");

  std::string theme = lua["config"]["ui"]["theme"];
  std::cout << theme << std::endl;
  config.theme = theme;

  // lua.script_file("~/.config/kean/init.lua");
  lua.script_file(std::string(std::getenv("HOME")) + "/.config/kean/init.lua");
  theme = lua["config"]["ui"]["theme"];
  std::cout << theme << std::endl;
  config.theme = theme;
}
