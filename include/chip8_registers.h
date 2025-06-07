#ifndef CHIP8_REGISTERS_H
#define CHIP8_REGISTERS_H

#include <stdint.h>
#include "config.h"

struct chip8_registers
{
    // I wont restrict this V register to programs to use.
    uint8_t V[CHIP8_TOTAL_DATA_REGISTERS];
    uint16_t I;
    uint8_t DT;
    uint8_t ST;
    uint16_t PC;
    uint8_t SP;
};


#endif