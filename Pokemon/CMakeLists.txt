cmake_minimum_required(VERSION 3.7)
project(Pokemon)
set(CMAKE_CXX_STANDARD 14)

ADD_LIBRARY(main
        code/src/game.cpp
        code/src/graphics.cpp
        )

include_directories(./code/headers/)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(pokemon code/src/main.cpp)
target_link_libraries(pokemon ${SDL2_LIBRARIES} main)
