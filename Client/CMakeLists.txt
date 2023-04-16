cmake_minimum_required(VERSION 3.21)

project(Client)

set(CMAKE_CXX_STANDARD 20)

set(CLIENT_SOURCES Client.cpp)

add_library(client SHARED ${CLIENT_SOURCES})