#ifndef EMULATOR_H
#define EMULATOR_H

#include <array>
#include <stack>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

class Emulator
{
public:
    Emulator(const std::string &fileName);
    void runCycle();
    unsigned char waitForInput();
private:
    std::ifstream stream;
    std::vector<unsigned char> data;
    std::array<unsigned char, 4096> memory;
    std::array<unsigned char, 16> V;
    std::array<unsigned char, 64 * 32> pixels;
    std::array<unsigned char, 80> font;
    std::array<unsigned char, 16> keys;
    std::array<unsigned short, 16> stack;
    unsigned short opcode;
    unsigned short I;
    unsigned short pc;
    unsigned char delayTimer;
    unsigned char soundTimer;
    unsigned char sp;
};

#endif
