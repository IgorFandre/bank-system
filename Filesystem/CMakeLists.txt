cmake_minimum_required(VERSION 3.21)

project(Filesystem)

set(CMAKE_CXX_STANDARD 20)

set(FILESYSTEM_SOURCES
        Filesystem.cpp
        )

add_library(filesystem SHARED ${FILESYSTEM_SOURCES})