#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H
#include "config.h"
#include <stdint.h>

struct chip8_memory
{
    uint8_t memory[CHIP8_MEMORY_SIZE];
};

void chip8_memory_set(struct chip8_memory *memory, int index, uint8_t val);
uint8_t chip8_memory_get(struct chip8_memory *memory, int index);


#endif