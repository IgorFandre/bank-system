cmake_minimum_required(VERSION 3.21)

project(Worker)

set(CMAKE_CXX_STANDARD 20)

set(WORKER_SOURCES
        Worker.cpp
        WorkerVisitor.cpp
        )

add_library(worker SHARED ${WORKER_SOURCES})