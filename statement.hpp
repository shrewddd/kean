#pragma once
#include <cstdint>
#include <sqlite3.h>
#include <string_view>

class Statement final {
public:

  Statement(const Statement&) = delete;
  Statement& operator=(const Statement&) = delete;
  Statement(Statement&& other) noexcept;
  Statement& operator=(Statement&& other) noexcept;
  ~Statement();
  
  void bind(int index, std::int64_t value);
  void bind(int index, std::string_view value);
  void bind_null(int index);
  void reset();
  void clear_bindings();

private:
  friend class Database;
  explicit Statement(sqlite3_stmt* statement) noexcept;

  sqlite3_stmt* statement_ = nullptr;
};
