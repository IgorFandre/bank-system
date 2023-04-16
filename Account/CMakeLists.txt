cmake_minimum_required(VERSION 3.21)

project(Accounts)

set(CMAKE_CXX_STANDARD 20)

set(ACCOUNT_SOURCES
        Account.cpp
        CreditAccount.cpp
        DebitAccount.cpp
        DepositAccount.cpp
        AccountFabric.cpp
)

add_library(accounts SHARED ${ACCOUNT_SOURCES})