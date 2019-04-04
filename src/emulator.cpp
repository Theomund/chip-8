#include "emulator.h"

Emulator::Emulator(const std::string &fileName)
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
    stream.open(fileName, std::ios::in | std::ios::binary);
    std::copy(std::istream_iterator<unsigned char>(stream), std::istream_iterator<unsigned char>(), memory.begin() + pc);
    stream.close();
}

void Emulator::runCycle()
{
    opcode = static_cast<unsigned short>(memory.at(pc) << 8 | memory.at(pc + 1));

    unsigned char n = opcode & 0x000F;
    unsigned char nn = opcode & 0x00FF;
    unsigned short nnn = opcode & 0x0FFF;
    unsigned char x = (opcode >> 8) & 0x000F;
    unsigned char y = (opcode >> 4) & 0x000F;

    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (nn)
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
        pc += (V.at(x) == nn) ? 2 : 0;
        break;
    case 0x4000:
        pc += (V.at(x) != nn) ? 2 : 0;
        break;
    case 0x5000:
        pc += (V.at(x) == V.at(y)) ? 2 : 0;
        break;
    case 0x6000:
        V.at(x) = nn;
        break;
    case 0x7000:
        V.at(x) += nn;
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
            V.at(0xF) = (V.at(y) > (0xFF - V.at(x))) ? 1 : 0;
            V.at(x) += V.at(y);
            break;
        case 0x5:
            V.at(x) -= V.at(y);
            break;
        case 0x6:
            V.at(0xF) = V.at(x) & 0x1;
            V.at(x) >>= 1;
            break;
        case 0x7:
            V.at(0xF) = (V.at(y) < V.at(x)) ? 1 : 0;
            V.at(x) = V.at(y) - V.at(x);
            break;
        case 0xE:
            V.at(0xF) = (V.at(x) >> 7) & 0x1;
            V.at(x) <<= 1;
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
        V.at(x) = std::rand() & nn;
        break;
    case 0xD000:
        break;
    case 0xE000:
        switch (nn)
        {
        case 0x9E:
            if (keys.at(V.at(x)) != 0)
            {
                pc += 2;
            }
            break;
        case 0xA1:
            if (keys.at(V.at(x)) == 0)
            {
                pc += 2;
            }
            break;
        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
        }
        break;
    case 0xF000:
        switch (nn)
        {
        case 0x07:
            V.at(x) = delayTimer;
            break;
        case 0x0A:
            V.at(x) = waitForInput();
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
            I = pixels.at(V.at(x));
            break;
        case 0x33:
            memory[I] = V[x] / 100;
            memory[I + 1] = (V[x] / 10) % 10;
            memory[I + 2] = (V[x] % 100) % 10;
            break;
        case 0x55:
            for (size_t i = 0; i <= x; i++)
            {
                memory.at(I + i) = V.at(i);
            }
            break;
        case 0x65:
            for (size_t i = 0; i <= x; i++)
            {
                V.at(i) = memory.at(I + i);
            }
            break;
        default:
            std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
        }
        break;
    default:
        std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
        break;
    }

    pc += 2;

    if (delayTimer > 0)
    {
        --delayTimer;
    }

    if (soundTimer > 0)
    {
        --soundTimer;
    }
}

unsigned char Emulator::waitForInput()
{
    while (true)
    {
        for (auto key : keys)
        {
            if (key != 0)
            {
                return key;
            }
        }
    }
}
