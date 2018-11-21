cmake_minimum_required(VERSION 3.12)
project(Queue_task)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -static)
add_executable(Queue_task main.cpp)