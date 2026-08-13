#include "statement.hpp"
#include <cstdint>

Statement::Statement(sqlite3_stmt* statement) noexcept: statement_(statement) {}

Statement::Statement(Statement&& other) noexcept : statement_(other.statement_) {
  other.statement_ = nullptr;
}

Statement& Statement::operator=(Statement&& other) noexcept {
  if (this != &other) {
    sqlite3_finalize(statement_);
    statement_ = other.statement_;
    other.statement_ = nullptr;
  }
  return *this;
}

Statement::~Statement() {
  sqlite3_finalize(statement_);
}

void Statement::bind(int index, std::int64_t value) {
  sqlite3_bind_int64(statement_, index, value);
}

void Statement::bind_null(int index) {
  sqlite3_bind_null(statement_, index);
}

void Statement::reset() {
  sqlite3_reset(statement_);
}

void Statement::clear_bindings() {
  sqlite3_clear_bindings(statement_);
}
