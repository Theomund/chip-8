#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL2/SDL.h"
#include <array>
#include <cstdint>

class Keyboard
{
public:
    Keyboard();
    unsigned char getKey(unsigned int index) const;
    unsigned char waitForInput();
    void poll(bool &quitPressed);

private:
    std::array<unsigned char, 16> keys;
    bool quit;
};

#endif
