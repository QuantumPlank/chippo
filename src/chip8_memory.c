#include"chip8_memory.h"
#include<assert.h>

static void chip8_is_memory_in_bounds(int index){
    assert((index >= 0) && (index < CHIP8_MEMORY_SIZE));
}

void chip8_memory_set(struct chip8_memory* memory, int index, unsigned char value){
    chip8_is_memory_in_bounds(index);
    memory->memory[index] = value;
}

unsigned char chip8_memory_get(struct chip8_memory* memory, int index){
    chip8_is_memory_in_bounds(index);
    return memory->memory[index];
}

unsigned short chip8_memory_get_short(struct chip8_memory* memory, int index){
    unsigned char byte1 = chip8_memory_get(memory, index);
    unsigned char byte2 = chip8_memory_get(memory, index+1);
    return (byte1 << 8) | byte2;
}