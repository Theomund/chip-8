#ifndef MEMORY_H
#define MEMORY_H

#include "font.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <stack>

class Memory
{
public:
    Memory();
    unsigned char getAddress(const unsigned int index) const;
    void setAddress(const unsigned int index, const unsigned char value);
    void loadFont(const Font &font);
    void loadROM(const std::string &name);
    void push(unsigned short address);
    unsigned short pop();

private:
    std::array<unsigned char, 4096> addresses;
    std::stack<unsigned short> stack;
};

#endif
