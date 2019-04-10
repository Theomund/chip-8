#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL2/SDL.h"

#include <array>
#include <cstdint>

class Keyboard {
  public:
    Keyboard();
    std::uint8_t getKey(std::uint32_t index) const;
    std::uint8_t waitForInput();
    void poll(bool &quitPressed);

  private:
    std::array<std::uint8_t, 16> keys;
    bool quit;
};

#endif
