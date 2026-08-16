#include "core_collector.hpp"
#include "db.hpp"
#include "mac.hpp"
#include "config.hpp"
#include "app_paths.hpp"
#include "migrate.hpp"

int main() {
  const AppPaths paths { resolve_app_paths() };
  const Config config { load_config(paths.config_file()) };
  CoreCollector collector {};
  MacEventSource source {};

  std::filesystem::create_directories(paths.data_directory);

  Database db { paths.database_file() };

  source.run(collector);
}
