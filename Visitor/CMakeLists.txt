cmake_minimum_required(VERSION 3.21)

project(Builder)

set(CMAKE_CXX_STANDARD 20)

set(VISITOR_SOURCES Visitor.cpp)

add_library(visitor SHARED ${VISITOR_SOURCES})