#pragma once
#include "db.hpp"
#include "migration.hpp"
#include <span>

void migrate(Database &db, std::span<const Migration> migrations);
