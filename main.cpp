#include "core_collector.hpp"
#include "mac.hpp"
#include "config.hpp"

int main() {
  Config config{};
  load_config(config);

  CoreCollector collector {};
  MacEventSource source {};

  source.run(collector);

  return 0;
}
