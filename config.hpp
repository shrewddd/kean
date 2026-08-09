#pragma once
#include <string>

struct Config {
  std::string theme;
};

void load_config(Config& config);
