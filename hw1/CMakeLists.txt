cmake_minimum_required(VERSION 3.28)
project(HW1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -Werror")

add_executable(HW1 main.cpp
        Utilities.cpp
        Utilities.h
        Transaction.cpp
        Transaction.h
        BlockChain.cpp
        BlockChain.h
)
