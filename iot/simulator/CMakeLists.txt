cmake_minimum_required(VERSION 3.1)

project(Simulator)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

add_library(
  simlib
  simlib/utils.cpp
  simlib/pin.cpp
  simlib/led.cpp
)

target_link_libraries(
  simlib
  ncurses
)

add_executable(
  sim
  simlib/main.cpp
  src/energia.cpp
)

target_link_libraries(
  sim
  simlib
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER g++)
add_compile_options(
  -v
  -O0
  -g
  -fsanitize=address
  -Wall
)