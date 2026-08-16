#pragma once
#include <string_view>

struct Migration {
  std::string_view name;
  std::string_view sql;
};
