#ifndef EMULATOR_H
#define EMULATOR_H

#include "cpu.h"
#include "display.h"
#include "font.h"
#include "keyboard.h"
#include "memory.h"
#include <string>

/**
 * @brief An overarching class used for handling the many components of the
 * emulator.
 */
class Emulator
{
public:
    /**
     * @brief Reads a font and ROM into memory.
     * @param fileName The filename of the ROM to be read.
     */
    Emulator(const std::string &fileName);

    /**
     * @brief Executes one full emulation cycle.
     */
    void runCycle();

    /**
     * @brief Retrieves whether the quit key was pressed or not.
     * @return A boolean indicating the quit key status.
     */
    bool getQuitPressed();

private:
    CPU cpu;
    Memory memory;
    Keyboard keyboard;
    Display display;
    bool quitPressed;
};

#endif
