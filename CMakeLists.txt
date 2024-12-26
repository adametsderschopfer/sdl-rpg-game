cmake_minimum_required(VERSION 3.30)

# Vars
set(PROJECT_NAME sdl_rpg_game)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

add_executable(sdl_rpg_game src/main.cpp
        src/Game.cpp
        src/Game.h)

# External

#TODO: Понять, как правильно организовывать работу с зависимостью, их сборкой
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image)