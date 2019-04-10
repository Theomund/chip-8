#include "display.h"

Display::Display() : pixels{}, drawFlag(false) {
    SDL_Init(SDL_INIT_VIDEO);
    window =
        SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 512, 256, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::clear() {
    for (auto row : pixels) {
        row.fill(0);
    }
    drawFlag = true;
}

bool Display::getDrawFlag() const { return drawFlag; }

std::uint8_t Display::getPixel(std::uint32_t x, std::uint32_t y) const {
    return pixels.at(x).at(y);
}

void Display::setPixel(std::uint32_t x, std::uint32_t y, std::uint8_t value) {
    pixels.at(x).at(y) = value;
}

void Display::setDrawFlag(bool value) { drawFlag = value; }

void Display::draw() {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 8;
    rect.h = 8;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (std::uint32_t y = 0; y < pixels.size(); y++) {
        for (std::uint32_t x = 0; x < pixels.at(0).size(); x++) {
            rect.x = x * rect.w;
            rect.y = y * rect.h;
            if (pixels.at(y).at(x) == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }

    drawFlag = false;

    SDL_RenderPresent(renderer);
}
