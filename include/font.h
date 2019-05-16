#ifndef FONT_H
#define FONT_H

#include <array>
#include <cstdint>

/**
 * @brief A class representing the font used within many CHIP-8 programs.
 */
class Font
{
public:
    /**
     * @brief Initializes the character array with the hexadecimal values of the
     * digits.
     */
    Font();

    /**
     * @brief Retrieves a digit in the character array when given a index.
     * @param index The position of the digit.
     * @return Five bytes representing a digit.
     */
    std::array<unsigned char, 5> getCharacter(size_t index) const;

    /**
     * @brief Retrieves the size of the font.
     * @return The size of the font.
     */
    size_t getSize() const;

    /**
     * @brief Retrieves the height of a digit.
     * @return The height of the digit.
     */
    size_t getHeight() const;

private:
    std::array<std::array<unsigned char, 5>, 16> characters;
};

#endif
