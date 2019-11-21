cmake_minimum_required(VERSION 3.7)
project(Pokemon)
set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/code/headers/)
file(GLOB_RECURSE Main_SOURCES "${PROJECT_SOURCE_DIR}/code/src/*.cpp")
file(GLOB_RECURSE Fight_SOURCES "${PROJECT_SOURCE_DIR}/code/src/Fight/*.cpp")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIR})

add_executable(pokemon code/src/main.cpp ${Main_SOURCES} ${Fight_SOURCES})

target_link_libraries(pokemon
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})

# Because of the paths of the images etc.. -> i copy the content of the meda into the resulting executable directory so i can use paths like ./backgrounds/
add_custom_command(TARGET pokemon PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/content $<TARGET_FILE_DIR:pokemon>/content)