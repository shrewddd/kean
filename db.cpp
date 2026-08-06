#include <sqlite3.h>
#include <stdexcept>
#include <string>

class Database final {
public:
  explicit Database(const std::string &filename): Database(filename.c_str()) {}

  explicit Database(const char* filename) {
    if (int rc = sqlite3_open(filename, &_db); rc != SQLITE_OK) {
      std::string msg = sqlite3_errmsg(_db);
      sqlite3_close_v2(_db);
      throw std::runtime_error("sqlite3_open failed: " + msg);
    }
  }

  Database(const Database&) = delete; 

  Database& operator=(const Database&) = delete;

  Database(Database&& other) noexcept : _db(other._db) {
    other._db = nullptr;
  }

  Database& operator=(Database&& other) noexcept {
    if (this != &other) {
      sqlite3_close_v2(_db);
      _db = other._db;
      other._db = nullptr;
    }
    return *this;
  }

  ~Database() { 
    sqlite3_close_v2(_db);
  }

  void query(const std::string &sql) { query(sql.c_str()); }

  void query(const char* sql) {
    char *errMsg = nullptr;

    if (const int rc = sqlite3_exec(_db, sql, nullptr, nullptr, &errMsg); rc != SQLITE_OK) {
      const std::string msg = errMsg ? errMsg : "unknown error";
      sqlite3_free(errMsg);
      throw std::runtime_error("sqlite3_exec failed: " + msg);
    }
  }

private:
  sqlite3 *_db = nullptr;
};
