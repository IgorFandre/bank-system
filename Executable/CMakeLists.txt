cmake_minimum_required(VERSION 3.21)

project(Executable)

set(CMAKE_CXX_STANDARD 20)

set(EXEC_SOURCES
        Executable.cpp
        )

add_library(executable SHARED ${EXEC_SOURCES})