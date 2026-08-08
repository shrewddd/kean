cmake_minimum_required(VERSION 4.0)

project(
  kean
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_library(CARBON_LIB Carbon REQUIRED)
find_library(APPSERVICES_LIB ApplicationServices REQUIRED)

add_executable(kean
  main.cpp
  core_collector.cpp
  mac.cpp
)

target_link_libraries(kean
  ${CARBON_LIB}
  ${APPSERVICES_LIB}
)
