#ifndef MEMORY_H
#define MEMORY_H

#include "font.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <stack>

/**
 * @brief A class used for storing values within memory.
 */
class Memory
{
public:
    /**
     * @brief Initializes each variable to their default values.
     */
    Memory();

    /**
     * @brief Retrieves a value stored in memory when given an index.
     * @param index The memory address.
     * @return A value in memory.
     */
    unsigned char getAddress(const unsigned int index) const;

    /**
     * @brief Sets the value stored in memory when given an index and value.
     * @param index The memory address.
     * @param value The new value.
     */
    void setAddress(const unsigned int index, const unsigned char value);

    /**
     * @brief Loads a font in memory starting from 0x000.
     * @param font The font class used for reading.
     */
    void loadFont(const Font &font);

    /**
     * @brief Loads a ROM into memory starting from 0x200.
     * @param name The filename of the ROM to read from.
     */
    void loadROM(const std::string &name);

    /**
     * @brief Pushes a memory address into the stack.
     * @param address The memory address.
     */
    void push(unsigned short address);

    /**
     * @brief Pops a memory address from the stack.
     * @return A memory address.
     */
    unsigned short pop();

private:
    std::array<unsigned char, 4096> addresses;
    std::stack<unsigned short> stack;
};

#endif
