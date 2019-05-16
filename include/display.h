#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL2/SDL.h"
#include <array>
#include <cstdint>
#include <memory>

/**
 * @brief A class for handling the window and renderer of the application.
 */
class Display
{
public:
    /**
     * @brief Initializes SDL and creates a window and renderer.
     */
    Display();

    /**
     * @brief Destroys the window and renderer, and then quits SDL.
     */
    ~Display();

    /**
     * @brief Clears the display screen.
     */
    void clear();

    /**
     * @brief Retrieves the pixel at coordinate (x,y) in the pixel array.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @return A pixel from the pixel array.
     */
    unsigned char getPixel(int x, int y) const;

    /**
     * @brief Sets a pixel at coordinate (x,y) to a given value.
     * @param x
     * @param y
     * @param value
     */
    void setPixel(unsigned int x, unsigned int y, unsigned char value);

    /**
     * @brief Sets the display draw flag.
     * @param value The new boolean value.
     */
    void setDrawFlag(bool value);

    /**
     * @brief Retrieves the display draw flag.
     * @return The display draw flag.
     */
    bool getDrawFlag() const;

    /**
     * @brief Draws rectangles on the screen according to the pixel array.
     */
    void draw();

private:
    std::array<std::array<unsigned char, 64>, 32> pixels;
    bool drawFlag;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif
