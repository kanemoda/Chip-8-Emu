#include "chip8_memory.h"
#include <assert.h>

static void chip8_check_memory_bounds(int index)
{
    assert(index >= 0 && index < CHIP8_MEMORY_SIZE);
}

void chip8_memory_set(chip8_memory *memory, int index, byte val)
{
    chip8_check_memory_bounds(index);
    memory->memory[index] = val;
}

byte chip8_memory_get(chip8_memory *memory, int index)
{
    chip8_check_memory_bounds(index);
    return memory->memory[index];
}