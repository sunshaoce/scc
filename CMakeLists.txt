cmake_minimum_required(VERSION 3.6)

project(scc C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(scc
  src/main.c
  src/preprocess.c
)

include_directories(include)
