#include "migrate.hpp"
#include "migration.hpp"
#include "statement.hpp"
#include <stdexcept>
#include <string>
#include <unordered_set>


void migrate(Database& db, std::span<const Migration> migrations) {
  db.query("CREATE TABLE IF NOT EXISTS migrations (name TEXT PRIMARY KEY);");

  auto query_migrations = db.prepare("SELECT * FROM migrations");

  std::unordered_set<std::string> applied_migrations {};

  while (query_migrations.step() == Statement::StepResult::row) {
    auto text = query_migrations.column_text(0);
    if (!text) throw std::runtime_error("null migration name");
    applied_migrations.emplace(reinterpret_cast<const char *>(text));
  }

  auto insert_migration = db.prepare("INSERT INTO migrations (name) VALUES ($1)");

  for(auto migration : migrations) {
    if (applied_migrations.contains(std::string{migration.name})) 
      continue;
    db.query(migration.sql);
    insert_migration.bind(1, migration.name);
    insert_migration.step();
    insert_migration.reset();
  }
}
