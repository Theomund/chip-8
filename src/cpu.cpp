#include "cpu.h"

CPU::CPU()
    : V{}, opcode(0), PC(0x200), I(0), NNN(0), NN(0), N(0), X(0), Y(0),
      delayTimer(0), soundTimer(0) {}

void CPU::fetch(Memory &memory) {
    opcode = static_cast<unsigned short>(memory.getAddress(PC) << 8 |
                                         memory.getAddress(PC + 1));
}

void CPU::decode() {
    N = opcode & 0x000F;
    NN = opcode & 0x00FF;
    NNN = opcode & 0x0FFF;
    X = (opcode >> 8) & 0x000F;
    Y = (opcode >> 4) & 0x000F;
}

void CPU::execute(Display &display, Keyboard &keyboard, Memory &memory) {
    switch (opcode & 0xF000) {
    case 0x0000:
        switch (NN) {
        case 0x00E0:
            display.clear();
            PC += 2;
            break;
        case 0x00EE:
            PC = memory.pop();
            break;
        default:
            throw std::runtime_error("Unknown opcode");
        }
        break;
    case 0x1000:
        PC = NNN;
        break;
    case 0x2000:
        memory.push(PC + 2);
        PC = NNN;
        break;
    case 0x3000:
        PC += (V.at(X) == NN) ? 4 : 2;
        break;
    case 0x4000:
        PC += (V.at(X) != NN) ? 4 : 2;
        break;
    case 0x5000:
        PC += (V.at(X) != V.at(Y)) ? 4 : 2;
        break;
    case 0x6000:
        V.at(X) = NN;
        PC += 2;
        break;
    case 0x7000:
        V.at(X) += NN;
        PC += 2;
        break;
    case 0x8000:
        switch (N) {
        case 0x0000:
            V.at(X) = V.at(Y);
            PC += 2;
            break;
        case 0x0001:
            V.at(X) |= V.at(Y);
            PC += 2;
            break;
        case 0x0002:
            V.at(X) &= V.at(Y);
            PC += 2;
            break;
        case 0x0003:
            V.at(X) ^= V.at(Y);
            PC += 2;
            break;
        case 0x0004:
            V.at(0xF) = (V.at(Y) > (0xFF - V.at(X))) ? 1 : 0;
            V.at(X) += V.at(Y);
            PC += 2;
            break;
        case 0x0005:
            V.at(0xF) = (V.at(Y) > V.at(X)) ? 0 : 1;
            V.at(X) -= V.at(Y);
            PC += 2;
            break;
        case 0x0006:
            V.at(0xF) = V.at(X) & 0x1;
            V.at(X) >>= 1;
            PC += 2;
            break;
        case 0x0007:
            V.at(0xF) = (V.at(Y) < V.at(X)) ? 0 : 1;
            V.at(X) = V.at(Y) - V.at(X);
            PC += 2;
            break;
        case 0x000E:
            V.at(0xF) = (V.at(X) >> 7) & 0x1;
            V.at(X) <<= 1;
            PC += 2;
            break;
        default:
            throw std::runtime_error("Unknown opcode");
        }
        break;
    case 0x9000:
        PC += (V.at(X) != V.at(Y)) ? 4 : 2;
        break;
    case 0xA000:
        I = NNN;
        PC += 2;
        break;
    case 0xB000:
        PC = V.at(0) + NNN;
        break;
    case 0xC000:
        V.at(X) = (std::rand() % 256) & NN;
        PC += 2;
        break;
    case 0xD000:
        V.at(0xF) = 0;
        for (unsigned int byteIndex = 0; byteIndex < N; byteIndex++) {
            unsigned char byte = memory.getAddress(I + byteIndex);
            for (unsigned int bitIndex = 0; bitIndex < 8; bitIndex++) {
                unsigned char bit = (byte >> bitIndex) & 0x1;
                unsigned char pixel =
                    display.getPixel((V.at(X) + (7 - bitIndex)) % 64,
                                     (V.at(Y) + byteIndex) % 32);
                if (bit == 1 && pixel == 1) {
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
        switch (NN) {
        case 0x009E:
            PC += (keyboard.getKey(V.at(X)) != 0) ? 4 : 2;
            break;
        case 0x00A1:
            PC += (keyboard.getKey(V.at(X)) == 0) ? 4 : 2;
            break;
        default:
            throw std::runtime_error("Unknown opcode");
        }
        break;
    case 0xF000:
        switch (NN) {
        case 0x0007:
            V.at(X) = delayTimer;
            PC += 2;
            break;
        case 0x000A:
            V.at(X) = keyboard.waitForInput();
            PC += 2;
            break;
        case 0x0015:
            delayTimer = V.at(X);
            PC += 2;
            break;
        case 0x0018:
            soundTimer = V.at(X);
            PC += 2;
            break;
        case 0x001E:
            I += V.at(X);
            PC += 2;
            break;
        case 0x0029:
            I = 5 * V.at(X);
            PC += 2;
            break;
        case 0x0033:
            memory.setAddress(I, (V.at(X) % 1000) / 100);
            memory.setAddress(I + 1, (V.at(X) % 100) / 10);
            memory.setAddress(I + 2, V.at(X) % 10);
            PC += 2;
            break;
        case 0x0055:
            for (unsigned int i = 0; i <= X; i++) {
                memory.setAddress(I + i, V.at(i));
            }
            PC += 2;
            break;
        case 0x0065:
            for (unsigned int i = 0; i <= X; i++) {
                V.at(i) = memory.getAddress(I + i);
            }
            PC += 2;
            break;
        default:
            throw std::runtime_error("Unknown opcode");
        }
        break;
    default:
        throw std::runtime_error("Unknown opcode");
    }

    if (display.getDrawFlag()) {
        display.draw();
    }

    if (soundTimer > 0) {
        --soundTimer;
        if (soundTimer == 0) {
            std::cout << "Beep!" << std::endl;
        }
    }

    if (delayTimer > 0) {
        --delayTimer;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
