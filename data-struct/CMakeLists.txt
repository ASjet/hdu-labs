cmake_minimum_required(VERSION 3.5)

project(DataStruct)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    main
    src/main.cpp
)

add_executable(
    exp2-1
    src/exp2-1.cpp
)

add_executable(
    exp2-2-1
    src/exp2-2-1.cpp
)

add_executable(
    exp2-2-2
    src/exp2-2-2.cpp
)

add_executable(
    exp2-3-1
    src/exp2-3-1.cpp
)

add_executable(
    exp3-1-1
    src/exp3-1-1.cpp
)

add_executable(
    exp3-1-2
    src/exp3-1-2.cpp
)

add_executable(
    exp3-1-addon
    src/exp3-1-addon.cpp
)
add_executable(
    exp3-2-1
    src/exp3-2-1.cpp
)

add_executable(
    exp3-3
    src/exp3-3.cpp
)

add_executable(
    exp3-4
    src/exp3-4.cpp
)

add_executable(
    exp7-1
    src/exp7-1.cpp
)

add_executable(
    exp7-2
    src/exp7-2.cpp
)

add_executable(
    exp8-1
    src/exp8-1.cpp
)

add_executable(
    exp8-2
    src/exp8-2.cpp
)

# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAG "-Wall")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAG "-Wall")
add_compile_options(-O0 -g -fsanitize=address)
