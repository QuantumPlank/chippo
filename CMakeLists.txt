cmake_minimum_required(VERSION 3.28)

project(chippo
        VERSION 0.2
        DESCRIPTION "Chip-8 emulator"
        LANGUAGES C)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(apps)

