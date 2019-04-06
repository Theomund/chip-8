#ifndef DISPLAY_H
#define DISPLAY_H

#include <array>
#include <cstdint>

class Display {
  public:
    Display();
    void clear();

  private:
    std::array<std::array<std::uint16_t, 64>, 32> pixels;
};

#endif
