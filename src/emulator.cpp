#include "emulator.h"

Emulator::Emulator()
    : memory({}), V({}), pixels({}),
      font({0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70,
            0xF0, 0x10, 0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
            0x90, 0x90, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0,
            0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0, 0x10, 0x20, 0x40, 0x40,
            0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0, 0x10, 0xF0,
            0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0,
            0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0,
            0xF0, 0x80, 0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80}),
      keys({}), stack({}), opcode(0), I(0), pc(0x200),
      delayTimer(0), soundTimer(0), sp(0)
{
    std::copy(font.begin(), font.end(), memory.begin());
}

void Emulator::runCycle()
{
    opcode = static_cast<unsigned short>(memory.at(pc) << 8 | memory.at(pc + 1));

    unsigned short nnn = opcode & 0x0FFF;
    unsigned char n = opcode & 0x000F;
    unsigned char x = (opcode >> 8) & 0x000F;
    unsigned char y = (opcode >> 4) & 0x000F;
    unsigned char kk = opcode & 0x00FF;

    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (kk)
        {
        case 0x00E0:
            pixels.fill(0);
            break;
        case 0x00EE:
            pc = stack.at(--sp);
            break;
        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
            break;
        }
        break;
    case 0x1000:
        pc = nnn;
        break;
    case 0x2000:
        stack.at(sp++) = pc;
        pc = nnn;
        break;
    case 0x3000:
        pc += (V.at(x) == kk) ? 2 : 0;
        break;
    case 0x4000:
        pc += (V.at(x) != kk) ? 2 : 0;
        break;
    case 0x5000:
        pc += (V.at(x) == V.at(y)) ? 2 : 0;
        break;
    case 0x6000:
        V.at(x) = kk;
        break;
    case 0x7000:
        V.at(x) += kk;
        break;
    case 0x8000:
        switch (n)
        {
        case 0x0:
            V.at(x) = V.at(y);
            break;
        case 0x1:
            V.at(x) |= V.at(y);
            break;
        case 0x2:
            V.at(x) &= V.at(y);
            break;
        case 0x3:
            V.at(x) ^= V.at(y);
            break;
        case 0x4:
            V.at(x) += V.at(y);
            break;
        case 0x5:
            V.at(x) -= V.at(y);
            break;
        case 0x6:
            V.at(x) >>= 1;
            break;
        case 0x7:
            V.at(0xF) = (V.at(y) > V.at(x)) ? 1 : 0;
            break;
        case 0xE:
            V.at(0xF) = (V.at(x) >> 7) & 0x1;
            V.at(x) *= 2;
            break;
        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
        }
        break;
    case 0x9000:
        pc += (V.at(x) != V.at(y)) ? 2 : 0;
        break;
    case 0xA000:
        I = nnn;
        break;
    case 0xB000:
        pc = nnn + V.at(0);
        break;
    case 0xC000:
        break;
    case 0xD000:
        break;
    case 0xE000:
        switch (kk)
        {
        case 0x9E:
            break;
        case 0xA1:
            break;
        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
        }
        break;
    case 0xF000:
        switch (kk)
        {
        case 0x07:
            V.at(x) = delayTimer;
            break;
        case 0x0A:
            break;
        case 0x15:
            delayTimer = V.at(x);
            break;
        case 0x18:
            soundTimer = V.at(x);
            break;
        case 0x1E:
            I += V.at(x);
            break;
        case 0x29:
            break;
        case 0x33:
            break;
        case 0x55:
            break;
        case 0x65:
            break;
        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
        }
        break;
    default:
        std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
        break;
    }
}

