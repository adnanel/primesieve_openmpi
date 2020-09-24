cmake_minimum_required(VERSION 3.16)
include_directories (/usr/local/include/)

project(primesieve)

FIND_PACKAGE(MPI)
IF ( MPI_FOUND )
    SET(CMAKE_REQUIRED_INCLUDES "${MPI_INCLUDE_PATH};${CMAKE_REQUIRED_INCLUDES}")
    INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})
ENDIF()
message(STATUS "My exec libs ${LINK_LIBRARIES}")

set(CMAKE_CXX_STANDARD 14)
add_executable(primesieve main.cpp Sieve.cpp Sieve.h)

target_link_libraries(primesieve ${MPI_LIBRARIES})
