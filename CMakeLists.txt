cmake_minimum_required(VERSION 3.26)
project(magic)

set(CMAKE_CXX_STANDARD 11)

add_executable(magic main.cpp
        magic.ipp
        magic.hpp)
