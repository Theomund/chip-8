#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <array>
#include <cstdint>

class Keyboard {
  public:
    Keyboard();
    std::uint16_t getKey(std::uint16_t index) const;

  private:
    std::array<std::uint16_t, 16> keys;
};

#endif
