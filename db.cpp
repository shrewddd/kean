#include "db.hpp"
#include "statement.hpp"
#include <stdexcept>
#include <string_view>

Database::Database(const std::string &filename): Database(filename.c_str()) {}

Database::Database(const char* filename) {
  if (int rc = sqlite3_open(filename, &db_); rc != SQLITE_OK) {
    std::string msg = sqlite3_errmsg(db_);
    sqlite3_close_v2(db_);
    throw std::runtime_error("sqlite3_open failed: " + msg);
  }

  if (int rc = sqlite3_db_config(db_, SQLITE_DBCONFIG_ENABLE_FKEY, 1, nullptr); rc != SQLITE_OK) {
    sqlite3_close_v2(db_);
    throw std::runtime_error("sqlite3_db_config failed");
  }

}

Database::Database(Database&& other) noexcept : db_(other.db_) {
  other.db_ = nullptr;
}

Database& Database::operator=(Database&& other) noexcept {
  if (this != &other) {
    sqlite3_close_v2(db_);
    db_ = other.db_;
    other.db_ = nullptr;
  }
  return *this;
}

Database::~Database() { 
  sqlite3_close_v2(db_);
}

void Database::query(const std::string_view &sql) { query(sql.data()); }

void Database::query(const std::string &sql) { query(sql.c_str()); }

void Database::query(const char* sql) {
  char *errMsg = nullptr;

  if (const int rc = sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg); rc != SQLITE_OK) {
    const std::string msg = errMsg ? errMsg : "unknown error";
    sqlite3_free(errMsg);
    throw std::runtime_error("sqlite3_exec failed: " + msg);
  }
}

Statement Database::prepare(const std::string_view sql) {
  sqlite3_stmt* stmt = nullptr;

  if (int rc = sqlite3_prepare_v2(db_, sql.data(), static_cast<int>(sql.size()), &stmt, nullptr); rc != SQLITE_OK) {
    sqlite3_finalize(stmt);
    throw std::runtime_error("sqlite3_prepare_v2 failed");
  }

  return Statement{ stmt };
}
