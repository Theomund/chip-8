#ifndef FONT_H
#define FONT_H

#include <array>
#include <cstdint>

class Font
{
public:
    Font();
    std::array<unsigned char, 5> getCharacter(size_t index) const;
    size_t getSize() const;
    size_t getHeight() const;

private:
    std::array<std::array<unsigned char, 5>, 16> characters;
};

#endif
