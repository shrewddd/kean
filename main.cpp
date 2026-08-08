#include <sqlite3.h>
#include "core_collector.hpp"
#include "mac.hpp"
#include "mac.hpp"

int main() {
  CoreCollector collector {};
  MacEventSource source {};

  source.run(collector);

  return 0;
}
