#pragma once
#include "statement.hpp"
#include <sqlite3.h>
#include <string>

class Database final {
public:
  explicit Database(const std::string &filename);
  explicit Database(const char* filename);
  Database(const Database&) = delete;
  Database& operator=(const Database&) = delete;
  Database(Database&& other) noexcept;
  Database& operator=(Database&& other) noexcept;
  ~Database();
  void query(const std::string &sql);
  void query(const char* sql);
  Statement prepare(const std::string_view sql);

private:
  sqlite3* db_ = nullptr;
};
