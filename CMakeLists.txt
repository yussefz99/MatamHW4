cmake_minimum_required(VERSION 3.27)
project(MatamHW4)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Events)
include_directories(Players)

add_executable(MatamHW4
        Events/Event.h
        Players/Player.h
        main.cpp
        MatamStory.cpp
        MatamStory.h
        Utilities.cpp
        Utilities.h
        Players/Player.cpp
        Players/Job.h
        Players/Character.h
        Events/Event.cpp
        Events/SpecialEvent.h
        Events/Encounter.h
)
