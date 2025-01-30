cmake_minimum_required(VERSION 3.28)
project(HW4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -Werror")

add_executable(HW4
        main.cpp
        MatamStory.h
        MatamStory.cpp
        Utilities.h
        Utilities.cpp
        Players/Player.h
        Events/Event.h
        Players/Character.h
        Players/Player.cpp
        Players/Job.h
        Players/PlayerFactory.h
        ObjectFactory.h
        test.cpp
        ObjectFactory.cpp
        ObjectFactory.cpp
        Players/Job.cpp
        Players/Character.cpp
        Players/Character.cpp
        Events/Event.cpp
)