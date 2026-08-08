#pragma once
#include <cstdint>

struct KeyboardEvent {
  uint16_t keyCode;
  uint64_t flags;
};
