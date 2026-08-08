#include "core_collector.hpp"
#include "keyboard_event.hpp"

void CoreCollector::push(KeyboardEvent event) {
  // std::cout << event.keyCode << std::endl;
  buffer_.push_back(event);
}
