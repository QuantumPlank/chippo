add_library(chip8_memory STATIC chip8.c chip8_memory.c chip8_registers.c chip8_stack.c chip8_keyboard.c chip8_screen.c)

target_include_directories(chip8_memory
    PUBLIC
    ${SDL2_INCLUDE_DIRS})