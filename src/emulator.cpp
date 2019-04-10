#include "emulator.h"

Emulator::Emulator(const std::string &fileName) : quitPressed(false) {
    Font font;
    memory.loadFont(font);
    memory.loadROM(fileName);
}

void Emulator::runCycle() {
    keyboard.poll(quitPressed);
    cpu.fetch(memory);
    cpu.decode();
    cpu.execute(display, keyboard, memory);
}

bool Emulator::getQuitPressed() {
    return quitPressed;
}
