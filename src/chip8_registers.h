#ifndef CHIP8_REGISTERS_H
#define CHIP8_REGISTERS_H

#include"config.h"

struct chip8_registers{
    unsigned char V[CHIP8_TOTAL_DATA_REGISTERS];
    unsigned short I;
    unsigned short PC;
    unsigned char SP;
    unsigned char sound_timer;
    unsigned char delay_timer;
};

#endif