cmake_minimum_required(VERSION 3.26)
project(magic)

set(CMAKE_CXX_STANDARD 11)

add_executable(magic main.cpp
        magic.ipp
        magic.hpp)

add_executable(es1-2023-11-23 examples/esercitazioni-2023/11/23/es1.cpp
        magic.ipp
        magic.hpp)