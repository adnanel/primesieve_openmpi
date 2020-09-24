cmake_minimum_required(VERSION 3.17)

project(primesieve)

set(CMAKE_CXX_STANDARD 14)
add_executable(primesieve main.cpp Sieve.cpp Sieve.h)