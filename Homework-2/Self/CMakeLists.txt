cmake_minimum_required(VERSION 3.25)
project(Self)

set(CMAKE_CXX_STANDARD 14)

include_directories(Include)

add_executable(Self
        Include/Database.hpp
        Include/Concrete/TravelerInfo.hpp
        Src/Main.cpp
        Utils/Utils.cpp
        Include/Interfaces/IRecord.hpp Include/Interfaces/Record.hpp)
