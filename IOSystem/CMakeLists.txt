cmake_minimum_required(VERSION 3.21)

project(IOIostream)

set(CMAKE_CXX_STANDARD 20)

set(IOSYSTEM_SOURCES
        IOIostream.cpp
        )

add_library(io_system SHARED ${IOSYSTEM_SOURCES})