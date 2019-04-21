#ifndef FONT_H
#define FONT_H

#include <array>
#include <cstdint>

class Font {
  public:
    Font();
    std::array<std::uint8_t, 5> getCharacter(std::size_t index) const;
    std::size_t getSize() const;
    std::size_t getHeight() const;

  private:
    std::array<std::array<std::uint8_t, 5>, 16> characters;
};

#endif
