#pragma once
#include "keyboard_event.hpp"
#include <vector>


class CoreCollector final {
  public:
    void push(KeyboardEvent event);

  private: 
    std::vector<KeyboardEvent> buffer_;
};
