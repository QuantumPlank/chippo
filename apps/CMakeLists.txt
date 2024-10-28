add_executable(chippo chippo.c)

target_include_directories(chippo
    PUBLIC
    ${SDL2_INCLUDE_DIRS})

target_include_directories(chippo
    PUBLIC
    ../src)

target_link_libraries(chippo
    PUBLIC
    ${SDL2_LIBRARIES})

target_link_libraries(chippo
    PRIVATE
    chip8_memory)