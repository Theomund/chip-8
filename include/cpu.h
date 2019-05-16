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

/**
 * @brief A class for performing the instructions of a computer program.
 */
class CPU
{
public:
    /**
     * @brief Initializes all variables to their default values.
     */
    CPU();

    /**
     * @brief Fetches an operation code from memory.
     * @param memory The memory class to be read from.
     */
    void fetch(Memory &memory);

    /**
     * @brief Decodes the operation code and assigns nibbles.
     */
    void decode();

    /**
     * @brief Selects an instruction to execute based on the operation code.
     * @param display The display class to read/write from.
     * @param keyboard The keyboard class to read/write from.
     * @param memory The memory class to read/write from.
     */
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
