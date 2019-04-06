#ifndef CPU_H
#define CPU_H

#include "display.h"
#include "keyboard.h"
#include "memory.h"

#include <array>
#include <cstdint>

class CPU {
  public:
    CPU();
    void fetch(Memory &memory);
    void decode();
    void execute(Display &display, Keyboard &keyboard, Memory &memory);

  private:
    std::array<std::uint8_t, 16> V;
    std::uint16_t opcode;
    std::uint16_t PC;
    std::uint16_t I;
    std::uint16_t NNN;
    std::uint8_t NN;
    std::uint8_t N;
    std::uint8_t X;
    std::uint8_t Y;
    std::uint8_t delayTimer;
    std::uint8_t soundTimer;
};

#endif
