#include <iostream>
#include <sqlite3.h>
#include <string>

class Database {
public:
  explicit Database(const std::string &filename) {
    sqlite3_open(filename.c_str(), &_db);
  }
  ~Database() { sqlite3_close(_db); }

  void query(std::string &query) {
    char *errMsg;

    int resultCode = sqlite3_exec(_db, query.c_str(), NULL, 0, &errMsg);
    if (resultCode != SQLITE_OK) {
      std::cout << errMsg << std::endl;
      sqlite3_free(errMsg);
    } else {
      std::cout << "Sucess" << std::endl;
    }
  }

private:
  sqlite3 *_db;
};
