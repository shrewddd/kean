#include "app_paths.hpp"
#include <filesystem>
#include <cstdlib>

namespace {
std::filesystem::path get_env(const char* var_name) {
  const char *env = std::getenv(var_name);
  return env ? std::filesystem::path(env) : std::filesystem::path();
}

std::filesystem::path get_home_dir() {
  return get_env("HOME");
}

std::filesystem::path get_config_dir() {
  const auto config_dir = get_env("XDG_CONFIG_HOME");
  const auto home_dir = get_home_dir();
  return !config_dir.empty() 
    ? config_dir / "kean"
    : home_dir / ".config" / "kean";
}

std::filesystem::path get_data_dir() {
  const auto data_dir = get_env("XDG_DATA_HOME");
  const auto home_dir = get_home_dir();
  return !data_dir.empty() 
    ? data_dir / "kean"
    : home_dir / ".local" / "share" / "kean";
}
}

AppPaths resolve_app_paths() {
  return { get_config_dir(), get_data_dir() };
}
