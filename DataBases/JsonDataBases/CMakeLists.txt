cmake_minimum_required(VERSION 3.21)

project(JsonDataBases)

set(CMAKE_CXX_STANDARD 20)

set(JSON_DB_SOURCES
        JsonDBAccounts.cpp
        JsonDBBanks.cpp
        JsonDBClients.cpp
        JsonDBWorkers.cpp
        )

add_library(json_db SHARED ${JSON_DB_SOURCES})