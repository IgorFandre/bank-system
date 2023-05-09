cmake_minimum_required(VERSION 3.21)

project(Date)

set(CMAKE_CXX_STANDARD 20)

set(DATE_SOURCES
        Date.cpp
        DateSetter.cpp
        )

add_library(date SHARED ${DATE_SOURCES})