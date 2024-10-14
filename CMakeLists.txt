cmake_minimum_required(VERSION 3.28)

project(chippo
        VERSION 0.1
        DESCRIPTION "Chip-8 emulator"
        LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(apps)