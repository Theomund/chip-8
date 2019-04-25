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
    unsigned char getPixel(int x, int y) const;
    void setPixel(unsigned int x, unsigned int y, unsigned char value);
    void setDrawFlag(bool value);
    bool getDrawFlag() const;
    void draw();

  private:
    std::array<std::array<unsigned char, 64>, 32> pixels;
    bool drawFlag;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif
