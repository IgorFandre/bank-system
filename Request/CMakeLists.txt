cmake_minimum_required(VERSION 3.21)

project(Request)

set(CMAKE_CXX_STANDARD 20)

set(REQUEST_SOURCES Request.cpp)

add_library(request SHARED ${REQUEST_SOURCES})