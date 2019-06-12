cmake_minimum_required(VERSION 3.9)
project(Wet2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -DNDEBUG")

add_executable(Wet2 main.cpp library2.h AVLCounter.h library2.cpp Wet2Exceptions.h Schedule2.h HashTable.h BiDirectionalList.h)
