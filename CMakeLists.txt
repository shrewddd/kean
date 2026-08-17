cmake_minimum_required(VERSION 4.0)

project(
  kean
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_PREFIX_PATH /opt/homebrew/opt/lua@5.4)
find_package(Lua 5.4 REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_package(SQLite3 REQUIRED)
if(NOT TARGET SQLite3::SQLite3)
  add_library(SQLite3::SQLite3 ALIAS SQLite::SQLite3)
endif()

include(FetchContent)
FetchContent_Declare(sol2
  GIT_REPOSITORY https://github.com/ThePhD/sol2.git
  GIT_TAG v3.5.0)
FetchContent_MakeAvailable(sol2)

find_library(CARBON_LIB Carbon REQUIRED)
find_library(APPSERVICES_LIB ApplicationServices REQUIRED)

file(GLOB MIGRATION_SQL CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/migrations/*.up.sql"
)

set(GENERATED_MIGRATIONS_HPP
  "${CMAKE_CURRENT_BINARY_DIR}/generated/migrations.generated.hpp"
)

add_custom_command(
  OUTPUT "${GENERATED_MIGRATIONS_HPP}"
  COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/generate_migrations.py" "${GENERATED_MIGRATIONS_HPP}"
  DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/generate_migrations.py"
    ${MIGRATION_SQL}
  VERBATIM
)

add_executable(kean
  main.cpp
  core_collector.cpp
  mac.cpp
  config.cpp
  app_paths.cpp
  db.cpp
  statement.cpp
  migrate.cpp
  "${GENERATED_MIGRATIONS_HPP}"
)

target_include_directories(kean PRIVATE
  ${LUA_INCLUDE_DIR}
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(kean PRIVATE
  ${LUA_LIBRARIES}
  SQLite3::SQLite3
  sol2
  ${CARBON_LIB}
  ${APPSERVICES_LIB}
)
