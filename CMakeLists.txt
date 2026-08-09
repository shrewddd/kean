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

include(FetchContent)
FetchContent_Declare(sol2
  GIT_REPOSITORY https://github.com/ThePhD/sol2.git
  GIT_TAG v3.5.0)
FetchContent_MakeAvailable(sol2)

find_library(CARBON_LIB Carbon REQUIRED)
find_library(APPSERVICES_LIB ApplicationServices REQUIRED)

add_executable(kean
  main.cpp
  core_collector.cpp
  mac.cpp
  config.cpp
  app_paths.cpp
)

target_include_directories(kean PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(kean PRIVATE
  ${LUA_LIBRARIES}
  sol2
  ${CARBON_LIB}
  ${APPSERVICES_LIB}
)
