cmake_minimum_required(VERSION 3.21)

project(Builder)

set(CMAKE_CXX_STANDARD 20)

set(BUILDER_SOURCES Builder.cpp)

add_library(builder SHARED ${BUILDER_SOURCES})