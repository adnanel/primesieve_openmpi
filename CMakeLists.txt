cmake_minimum_required(VERSION 3.17)
include_directories (/usr/local/include/)

project(primesieve)

set(CMAKE_CXX_STANDARD 14)
add_executable(primesieve main.cpp Sieve.cpp Sieve.h)