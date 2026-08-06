#include "db.hpp"
#include <stdexcept>

Database::Database(const std::string &filename): Database(filename.c_str()) {}

Database::Database(const char* filename) {
  if (int rc = sqlite3_open(filename, &_db); rc != SQLITE_OK) {
    std::string msg = sqlite3_errmsg(_db);
    sqlite3_close_v2(_db);
    throw std::runtime_error("sqlite3_open failed: " + msg);
  }
}

Database::Database(Database&& other) noexcept : _db(other._db) {
  other._db = nullptr;
}

Database& Database::operator=(Database&& other) noexcept {
  if (this != &other) {
    sqlite3_close_v2(_db);
    _db = other._db;
    other._db = nullptr;
  }
  return *this;
}

Database::~Database() { 
  sqlite3_close_v2(_db);
}

void Database::query(const std::string &sql) { query(sql.c_str()); }

void Database::query(const char* sql) {
  char *errMsg = nullptr;

  if (const int rc = sqlite3_exec(_db, sql, nullptr, nullptr, &errMsg); rc != SQLITE_OK) {
    const std::string msg = errMsg ? errMsg : "unknown error";
    sqlite3_free(errMsg);
    throw std::runtime_error("sqlite3_exec failed: " + msg);
  }
}
