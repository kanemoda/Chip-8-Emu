#ifndef CHIP8_STACK_H
#define CHIP8_STACK_H

#include "config.h"
#include <stdint.h>

struct chip8;
struct chip8_stack
{
    uint16_t stack[CHIP8_TOTAL_STACK_DEPTH];
};

void chip8_stack_push(struct chip8* chip8, uint16_t val);
uint16_t chip8_stack_pop(struct chip8 *chip8);




#endif