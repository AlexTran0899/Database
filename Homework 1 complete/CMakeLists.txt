cmake_minimum_required(VERSION 3.25)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cpp
        DB.cpp
        DB.h
        testdb.cpp PassengerInfo.cpp PassengerInfo.h )
