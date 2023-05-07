cmake_minimum_required(VERSION 3.21)

project(BigInteger)

set(CMAKE_CXX_STANDARD 20)

set(BIGINT_SOURCES biginteger.cpp)

add_library(bigint SHARED ${BIGINT_SOURCES})