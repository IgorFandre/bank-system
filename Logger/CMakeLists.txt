cmake_minimum_required(VERSION 3.21)

project(Logger)

set(CMAKE_CXX_STANDARD 20)

set(LOGGER_SOURCES
        Logger.cpp
        )

add_library(logger SHARED ${LOGGER_SOURCES})