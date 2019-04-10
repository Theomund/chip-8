#ifndef MEMORY_H
#define MEMORY_H

#include "font.h"

#include <array>
#include <cstdint>
#include <fstream>
#include <stack>

class Memory {
  public:
    Memory();
    std::uint8_t getAddress(const std::uint32_t index) const;
    void setAddress(const std::uint32_t index, const std::uint8_t value);
    void loadFont(const Font &font);
    void loadROM(const std::string &name);
    void push(std::uint16_t address);
    std::uint16_t pop();

  private:
    std::array<std::uint8_t, 4096> addresses;
    std::stack<std::uint16_t> stack;
};

#endif
