#include "core_collector.hpp"
#include "mac.hpp"
#include "config.hpp"
#include "app_paths.hpp"

int main() {
  const AppPaths paths { resolve_app_paths() };
  const Config config { load_config(paths.config_file()) };
  CoreCollector collector {};
  MacEventSource source {};

  source.run(collector);
}
