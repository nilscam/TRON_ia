cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(toto main.cpp Snake.cpp Snake.h Cell.cpp Cell.h Map.cpp Map.h)