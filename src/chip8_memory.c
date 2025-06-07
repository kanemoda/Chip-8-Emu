#include "chip8_memory.h"
#include <assert.h>

static void chip8_is_memory_in_bounds(int index)
{
    assert(index >= 0 && index < CHIP8_MEMORY_SIZE);
}

void chip8_memory_set(struct chip8_memory *memory, int index, uint8_t val)
{
    chip8_is_memory_in_bounds(index);
    memory->memory[index] = val;
}
uint8_t chip8_memory_get(struct chip8_memory *memory, int index)
{
    return memory->memory[index];
}