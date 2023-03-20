cmake_minimum_required(VERSION 3.24)
project(bank_system)

set(CMAKE_CXX_STANDARD 20)
find_package(GTest REQUIRED)

include_directories(Account)
include_directories(Bank)
include_directories(Builder)
include_directories(Client)
include_directories(DataBases)
include_directories(DataBases/Interfaces)
include_directories(IOSystem)
include_directories(Request)
include_directories(Worker)

#add_executable(TEST_BANK google_tests.cpp)
#target_link_libraries(TEST_BANK GTest::gtest GTest::gtest_main)


add_executable(MAIN main.cpp)
