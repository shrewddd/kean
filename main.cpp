#include <sqlite3.h>
#include <string>
#include "db.hpp"
#include "mac.hpp"

int main() {
  const std::string filename = "db.sqlite3"; 
  Database db {filename};
  initialize_listener();
  return 0;
}
