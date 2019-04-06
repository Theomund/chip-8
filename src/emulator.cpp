#include "emulator.h"

Emulator::Emulator(const std::string &fileName) {
    Font font;
    memory.loadFont(font);
    memory.loadROM(fileName);
}

void Emulator::runCycle() {
    cpu.fetch(memory);
    cpu.decode();
    cpu.execute(display, keyboard, memory);
}
