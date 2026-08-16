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

void Statement::bind(int index, std::string_view value) {
  sqlite3_bind_text64(statement_, index, value.data(), value.size(), SQLITE_TRANSIENT, SQLITE_UTF8);
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

Statement::StepResult Statement::step() {
  int rc = sqlite3_step(statement_);
  if (rc == SQLITE_DONE)
    return StepResult::done;
  if (rc == SQLITE_ROW)
    return StepResult::row;
  throw std::runtime_error("sqlite3_step failed");
}

std::int64_t Statement::column_int64(int index) {
  return sqlite3_column_int64(statement_, index);
}

std::int32_t Statement::column_int(int index) {
  return sqlite3_column_int(statement_, index);
}

double Statement::column_double(int index) {
  return sqlite3_column_double(statement_, index);
}

const unsigned char * Statement::column_text(int index) {
  return sqlite3_column_text(statement_, index);
}
