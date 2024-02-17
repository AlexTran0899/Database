cmake_minimum_required(VERSION 3.25)
project(Self)

set(CMAKE_CXX_STANDARD 14)

include_directories(Include)

add_executable(Self
        Src/Main.cpp Include/Database.h Include/TravelerInfo.h Src/TravelerInfo.cpp)
