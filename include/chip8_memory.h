#ifndef CHIP_8_MEMORY_H
#define CHIP_8_MEMORY_H

#include "config.h"

typedef struct chip8_memory
{
    byte memory[CHIP8_MEMORY_SIZE];
} chip8_memory;

void chip8_memory_set(chip8_memory *memory, int index, byte val);
byte chip8_memory_get(chip8_memory *memory, int index);


#endif