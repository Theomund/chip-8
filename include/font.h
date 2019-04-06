#ifndef FONT_H
#define FONT_H

#include <array>
#include <cstdint>

class Font {
  public:
    Font();
    std::array<std::array<std::uint16_t, 5>, 16> getCharacters() const;

  private:
    std::array<std::array<std::uint16_t, 5>, 16> characters;
};

#endif
