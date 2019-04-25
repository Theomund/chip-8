#include "keyboard.h"

Keyboard::Keyboard() : keys{}, quit(false) {}

unsigned char Keyboard::getKey(unsigned int index) const {
    return keys.at(index);
}

unsigned char Keyboard::waitForInput() {
    while (true) {
        for (auto key : keys) {
            if (key != 0) {
                return key;
            }
        }
    }
}

void Keyboard::poll(bool &quitPressed) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            quitPressed = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_1:
                keys.at(0x1) = 1;
                break;
            case SDLK_2:
                keys.at(0x2) = 1;
                break;
            case SDLK_3:
                keys.at(0x3) = 1;
                break;
            case SDLK_4:
                keys.at(0xC) = 1;
                break;
            case SDLK_q:
                keys.at(0x4) = 1;
                break;
            case SDLK_w:
                keys.at(0x5) = 1;
                break;
            case SDLK_e:
                keys.at(0x6) = 1;
                break;
            case SDLK_r:
                keys.at(0xD) = 1;
                break;
            case SDLK_a:
                keys.at(0x7) = 1;
                break;
            case SDLK_s:
                keys.at(0x8) = 1;
                break;
            case SDLK_d:
                keys.at(0x9) = 1;
                break;
            case SDLK_f:
                keys.at(0xE) = 1;
                break;
            case SDLK_z:
                keys.at(0xA) = 1;
                break;
            case SDLK_x:
                keys.at(0x0) = 1;
                break;
            case SDLK_c:
                keys.at(0xB) = 1;
                break;
            case SDLK_v:
                keys.at(0xF) = 1;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
            case SDLK_1:
                keys.at(0x1) = 0;
                break;
            case SDLK_2:
                keys.at(0x2) = 0;
                break;
            case SDLK_3:
                keys.at(0x3) = 0;
                break;
            case SDLK_4:
                keys.at(0xC) = 0;
                break;
            case SDLK_q:
                keys.at(0x4) = 0;
                break;
            case SDLK_w:
                keys.at(0x5) = 0;
                break;
            case SDLK_e:
                keys.at(0x6) = 0;
                break;
            case SDLK_r:
                keys.at(0xD) = 0;
                break;
            case SDLK_a:
                keys.at(0x7) = 0;
                break;
            case SDLK_s:
                keys.at(0x8) = 0;
                break;
            case SDLK_d:
                keys.at(0x9) = 0;
                break;
            case SDLK_f:
                keys.at(0xE) = 0;
                break;
            case SDLK_z:
                keys.at(0xA) = 0;
                break;
            case SDLK_x:
                keys.at(0x0) = 0;
                break;
            case SDLK_c:
                keys.at(0xB) = 0;
                break;
            case SDLK_v:
                keys.at(0xF) = 0;
                break;
            }
            break;
        }
    }
}
