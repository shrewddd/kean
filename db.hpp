#include <sqlite3.h>
#include <string>

class Database {
public:
  Database(const std::string &filename);
  ~Database();
  void query(std::string &query);

private:
  sqlite3 *_db;
};
