#include "display.h"

Display::Display() : pixels{} {}

void Display::clear() {
    for (auto row : pixels) {
        row.fill(0);
    }
}
