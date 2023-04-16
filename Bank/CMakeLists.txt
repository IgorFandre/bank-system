cmake_minimum_required(VERSION 3.21)

project(Bank)

set(CMAKE_CXX_STANDARD 20)

set(BANK_SOURCES Bank.cpp)

add_library(bank SHARED ${BANK_SOURCES})