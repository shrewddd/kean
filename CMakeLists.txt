cmake_minimum_required(VERSION 4.0)

project(
  kean
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(CARBON_LIB Carbon REQUIRED)
find_library(APPSERVICES_LIB ApplicationServices REQUIRED)

find_package(SQLite3 REQUIRED)

add_executable(kean main.cpp db.cpp mac.cpp)

target_link_libraries(kean
  ${CARBON_LIB}
  ${APPSERVICES_LIB}
  SQLite::SQLite3
)

