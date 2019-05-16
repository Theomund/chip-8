#include "emulator.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        Emulator emulator(argv[1]);
        while (!emulator.getQuitPressed())
        {
            emulator.runCycle();
        }
    }
    else
    {
        std::cerr << "Usage: ./chip-8 [ROM]" << std::endl;
    }
    return 0;
}
