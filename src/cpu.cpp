#include "cpu.h"

CPU::CPU()
    : V{}, opcode(0), PC(0x200), I(0), NNN(0), NN(0), N(0), X(0), Y(0),
      delayTimer(0), soundTimer(0)
{
}

void CPU::fetch(Memory &memory)
{
    opcode = static_cast<unsigned short>(memory.getAddress(PC) << 8 |
                                         memory.getAddress(PC + 1));
}

void CPU::decode()
{
    N = opcode & 0x000F;
    NN = opcode & 0x00FF;
    NNN = opcode & 0x0FFF;
    X = (opcode >> 8) & 0x000F;
    Y = (opcode >> 4) & 0x000F;
}

void CPU::execute(Display &display, Keyboard &keyboard, Memory &memory)
{
    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (NN)
        {
        case 0x00E0:
            // CLS - Clear the display.
            display.clear();
            PC += 2;
            break;
        case 0x00EE:
            // RET - Return from a subroutine.
            PC = memory.pop();
            break;
        default:
            throw std::runtime_error("Unknown opcode");
        }
        break;
    case 0x1000:
        // JP - Jump to location NNN.
        PC = NNN;
        break;
    case 0x2000:
        // CALL - Call subroutine at NNN.
        memory.push(PC + 2);
        PC = NNN;
        break;
    case 0x3000:
        // SE - Skip next instruction if V[X] == NN.
        PC += (V.at(X) == NN) ? 4 : 2;
        break;
    case 0x4000:
        // SNE - Skip next instruction if V[X] != NN.
        PC += (V.at(X) != NN) ? 4 : 2;
        break;
    case 0x5000:
        // SE - Skip next instruction if V[X] == V[Y].
        PC += (V.at(X) == V.at(Y)) ? 4 : 2;
        break;
    case 0x6000:
        // LD - Set V[X] = NN.
        V.at(X) = NN;
        PC += 2;
        break;
    case 0x7000:
        // ADD - Set V[X] = V[X] + NN.
        V.at(X) += NN;
        PC += 2;
        break;
    case 0x8000:
        switch (N)
        {
        case 0x0000:
            // LD - Set V[X] = V[Y]
            V.at(X) = V.at(Y);
            break;
        case 0x0001:
            // OR - Set V[X] = V[X] || V[Y].
            V.at(X) |= V.at(Y);
            break;
        case 0x0002:
            // AND - Set V[X] = V[X] && V[Y].
            V.at(X) &= V.at(Y);
            break;
        case 0x0003:
            // XOR - Set V[X] = V[X] ^ V[Y].
            V.at(X) ^= V.at(Y);
            break;
        case 0x0004:
            // ADD - Set V[X] = V[X] + V[Y]; V[F] = carry.
            V.at(0xF) = (V.at(Y) > (0xFF - V.at(X))) ? 1 : 0;
            V.at(X) += V.at(Y);
            break;
        case 0x0005:
            // SUB - Set V[X] = V[X] - V[Y]; V[F] = NOT borrow.
            V.at(0xF) = (V.at(Y) > V.at(X)) ? 0 : 1;
            V.at(X) -= V.at(Y);
            break;
        case 0x0006:
            // SHR - Set V[X] = V[X] >> 1.
            V.at(0xF) = V.at(X) & 0x1;
            V.at(X) >>= 1;
            break;
        case 0x0007:
            // SUBN - Set V[X] = V[Y] - V[X]; V[F] = NOT borrow.
            V.at(0xF) = (V.at(Y) < V.at(X)) ? 0 : 1;
            V.at(X) = V.at(Y) - V.at(X);
            break;
        case 0x000E:
            // SHL - Set V[X] = V[X] << 1.
            V.at(0xF) = (V.at(X) >> 7) & 0x1;
            V.at(X) <<= 1;
            break;
        default:
            throw std::runtime_error("Unknown opcode");
        }
        PC += 2;
        break;
    case 0x9000:
        // SNE - Skip next instruction if V[X] != V[Y].
        PC += (V.at(X) != V.at(Y)) ? 4 : 2;
        break;
    case 0xA000:
        // LD - Set I = NNN.
        I = NNN;
        PC += 2;
        break;
    case 0xB000:
        // JP - Jump to location NNN + V[0].
        PC = V.at(0) + NNN;
        break;
    case 0xC000:
        // RND - Set V[X] = random byte && NN.
        V.at(X) = (std::rand() % 256) & NN;
        PC += 2;
        break;
    case 0xD000:
        // DRW - Display N-byte sprite starting at memory location I at (V[X],
        // V[Y]); V[F] = collision.
        V.at(0xF) = 0;
        for (unsigned int byteIndex = 0; byteIndex < N; byteIndex++)
        {
            unsigned char byte = memory.getAddress(I + byteIndex);
            for (unsigned int bitIndex = 0; bitIndex < 8; bitIndex++)
            {
                unsigned char bit = (byte >> bitIndex) & 0x1;
                unsigned char pixel =
                    display.getPixel((V.at(X) + (7 - bitIndex)) % 64,
                                     (V.at(Y) + byteIndex) % 32);
                if (bit == 1 && pixel == 1)
                {
                    V.at(0xF) = 1;
                }
                display.setPixel((V.at(X) + (7 - bitIndex)) % 64,
                                 (V.at(Y) + byteIndex) % 32, pixel ^= bit);
            }
        }
        display.setDrawFlag(true);
        PC += 2;
        break;
    case 0xE000:
        switch (NN)
        {
        case 0x009E:
            // SKP - Skip next instruction if key with the value of V[X] is
            // pressed.
            PC += (keyboard.getKey(V.at(X)) != 0) ? 4 : 2;
            break;
        case 0x00A1:
            // SKNP - Skip next instruction if key with the value of V[X] is not
            // pressed.
            PC += (keyboard.getKey(V.at(X)) == 0) ? 4 : 2;
            break;
        default:
            throw std::runtime_error("Unknown opcode");
        }
        break;
    case 0xF000:
        switch (NN)
        {
        case 0x0007:
            // LD - Set V[X] = delay timer value.
            V.at(X) = delayTimer;
            break;
        case 0x000A:
            // LD - Wait for a key press, and store the value of the key in
            // V[X].
            V.at(X) = keyboard.waitForInput();
            break;
        case 0x0015:
            // LD - Set delay timer = V[X].
            delayTimer = V.at(X);
            break;
        case 0x0018:
            // LD - Set sound timer = V[X].
            soundTimer = V.at(X);
            break;
        case 0x001E:
            // ADD - Set I = I + V[X].
            I += V.at(X);
            break;
        case 0x0029:
            // LD - Set I = location of sprite for digit V[X].
            I = 5 * V.at(X);
            break;
        case 0x0033:
            // LD - Store BCD representation of V[X] in memory locations I, I +
            // 1, and I + 2.
            memory.setAddress(I, (V.at(X) % 1000) / 100);
            memory.setAddress(I + 1, (V.at(X) % 100) / 10);
            memory.setAddress(I + 2, V.at(X) % 10);
            break;
        case 0x0055:
            // LD - Store registers V[0] through V[X] in memory starting at
            // location I.
            for (unsigned int i = 0; i <= X; i++)
            {
                memory.setAddress(I + i, V.at(i));
            }
            break;
        case 0x0065:
            // LD - Read registers V[0] through V[X] from memory starting at
            // location I.
            for (unsigned int i = 0; i <= X; i++)
            {
                V.at(i) = memory.getAddress(I + i);
            }
            break;
        default:
            throw std::runtime_error("Unknown opcode");
        }
        PC += 2;
        break;
    default:
        throw std::runtime_error("Unknown opcode");
    }

    if (display.getDrawFlag())
    {
        display.draw();
    }

    if (soundTimer > 0)
    {
        --soundTimer;
    }

    if (delayTimer > 0)
    {
        --delayTimer;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
