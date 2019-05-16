#ifndef EMULATOR_H
#define EMULATOR_H

#include "cpu.h"
#include "display.h"
#include "font.h"
#include "keyboard.h"
#include "memory.h"
#include <string>

class Emulator
{
public:
    Emulator(const std::string &fileName);
    void runCycle();
    bool getQuitPressed();

private:
    CPU cpu;
    Memory memory;
    Keyboard keyboard;
    Display display;
    bool quitPressed;
};

#endif
