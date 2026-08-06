#include <iostream>
#include <sqlite3.h>
#include <string>

class Database {
public:
  explicit Database(const std::string &filename): Database(filename.c_str()) {}

  explicit Database(const char* filename) {
    sqlite3_open(filename, &_db);
  }

  ~Database() { sqlite3_close(_db); }

  void query(const std::string &sql) { 
    query(sql.c_str());
  }

  void query(const char* sql) {
    char *errMsg = nullptr;

    int resultCode = sqlite3_exec(_db, sql, nullptr, 0, &errMsg);
    if (resultCode != SQLITE_OK) {
      std::cout << errMsg << std::endl;
      sqlite3_free(errMsg);
    } else {
      std::cout << "Success" << std::endl;
    }
  }

private:
  sqlite3 *_db;
};
