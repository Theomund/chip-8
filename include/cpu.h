#ifndef CPU_H
#define CPU_H

#include "display.h"
#include "keyboard.h"
#include "memory.h"
#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <thread>

class CPU
{
public:
    CPU();
    void fetch(Memory &memory);
    void decode();
    void execute(Display &display, Keyboard &keyboard, Memory &memory);

private:
    std::array<unsigned char, 16> V;
    unsigned short opcode;
    unsigned short PC;
    unsigned short I;
    unsigned short NNN;
    unsigned char NN;
    unsigned char N;
    unsigned char X;
    unsigned char Y;
    unsigned char delayTimer;
    unsigned char soundTimer;
};

#endif
