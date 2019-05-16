#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SDL2/SDL.h"
#include <array>
#include <cstdint>

/**
 * @brief A class used for capturing input from a keyboard.
 */
class Keyboard
{
public:
    /**
     * @brief Initializes each variable to their default values.
     */
    Keyboard();

    /**
     * @brief Gets a key from the key array when given an index.
     * @param index The position of the key.
     * @return The value of a key.
     */
    unsigned char getKey(unsigned int index) const;

    /**
     * @brief Waits until a key has been pressed.
     * @return The key that has been pressed.
     */
    unsigned char waitForInput();

    /**
     * @brief Polls for input events.
     * @param quitPressed A reference to the boolean stored within the emulator
     * class.
     */
    void poll(bool &quitPressed);

private:
    std::array<unsigned char, 16> keys;
    bool quit;
};

#endif
