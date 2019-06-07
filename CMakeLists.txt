cmake_minimum_required(VERSION 2.8.4)
project(DataStructureWet2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -DNDEBUG")

add_executable(DataStructureWet2 main.cpp  library2.h)