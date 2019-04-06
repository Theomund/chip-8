#include "keyboard.h"

Keyboard::Keyboard() : keys{} {}

std::uint16_t Keyboard::getKey(std::uint16_t index) const {
    return keys.at(index);
}
