#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL2/SDL.h"

#include <array>
#include <cstdint>
#include <memory>

class Display {
  public:
    Display();
    ~Display();
    void clear();
    std::uint8_t getPixel(std::uint32_t x, std::uint32_t y) const;
    void setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t value);
    void setDrawFlag(bool value);
    bool getDrawFlag() const;
    void draw();

  private:
    std::array<std::array<std::uint8_t, 64>, 32> pixels;
    bool drawFlag;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif
