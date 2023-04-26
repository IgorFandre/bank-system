# -------------------------------------------

cmake_minimum_required(VERSION 3.21)

# -------------------------------------------

project(bank_system
        VERSION 1.0.0
        DESCRIPTION "Good job"
        )

# -------------------------------------------
# Some basic settings
# -------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(GTest REQUIRED)

# -------------------------------------------
# Little acceleration
# -------------------------------------------

SET(GCC_COVERAGE_COMPILE_FLAGS "-O2")
SET(CMAKE_CXX_FLAGS  "${GCC_COVERAGE_COMPILE_FLAGS}")

# -------------------------------------------
# Shared libraries
# -------------------------------------------

add_subdirectory(Filesystem)

add_subdirectory(IOSystem)

add_subdirectory(Request)
add_dependencies(request filesystem)
target_link_libraries(request filesystem)

add_subdirectory(Logger)
add_dependencies(logger filesystem)
target_link_libraries(logger filesystem)

add_subdirectory(Date)
add_dependencies(date filesystem)
target_link_libraries(date filesystem)

add_subdirectory(Account)
add_dependencies(accounts date)
target_link_libraries(accounts date)

add_subdirectory(Client)
add_dependencies(client date)
target_link_libraries(client date)

add_subdirectory(Bank)

add_subdirectory(Worker)
add_dependencies(worker client date logger request)
target_link_libraries(worker client date logger request)

add_subdirectory(Builder)
add_dependencies(builder accounts bank io_system request worker)
target_link_libraries(builder accounts bank io_system request worker)

add_subdirectory(Visitor)
add_dependencies(visitor client date logger builder)
target_link_libraries(visitor client date logger builder)


add_subdirectory(DataBases/JsonDataBases)
add_dependencies(json_db accounts worker)
target_link_libraries(json_db accounts bank worker)


add_subdirectory(Executable)
add_dependencies(executable json_db visitor)
target_link_libraries(executable json_db visitor)

# -------------------------------------------
# Executable tests
# -------------------------------------------

set(TEST_SOURCES
        # -------------------------------------------
        # Test cases
        # -------------------------------------------

        tests/TestCases/AccountTestCase/tests.cpp

        tests/TestCases/BankTestCase/tests.cpp

        tests/TestCases/ClientTestCase/tests_passport.cpp

        tests/TestCases/ClientTestCase/tests_client.cpp

        tests/TestCases/DateTestCase/tests.cpp

        tests/TestCases/DBAccountsTestCase/tests.cpp

        tests/TestCases/DBBanksTestCase/tests.cpp

        tests/TestCases/DBClientsTestCase/tests.cpp

        tests/TestCases/DBWorkersTestCase/tests.cpp

        tests/TestCases/FileSystemTestCase/tests.cpp

        tests/TestCases/LoggerTestCase/tests.cpp

        tests/TestCases/RequestTestCase/tests.cpp

        # -------------------------------------------
        # Main File
        # -------------------------------------------

        google_tests.cpp

)
add_executable(TEST_BANK ${TEST_SOURCES})
add_dependencies(TEST_BANK executable)
target_link_libraries(
        TEST_BANK
        GTest::gtest
        GTest::gtest_main
        executable
)

# -------------------------------------------
# Executable main
# -------------------------------------------

add_executable(MAIN main.cpp)
add_dependencies(MAIN executable)
target_link_libraries(
        MAIN
        executable
)

# -------------------------------------------