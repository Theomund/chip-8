#include "memory.h"
#include <iostream>

Memory::Memory() : addresses{} {}

std::uint8_t Memory::getAddress(const std::uint32_t index) const {
    return static_cast<std::uint8_t>(addresses.at(index));
}

void Memory::setAddress(const std::uint32_t index, const std::uint8_t value) {
    addresses.at(index) = value;
}

void Memory::loadROM(const std::string &name) {
    std::ifstream stream(name, std::ios::binary | std::ios::in);
    if (stream.is_open()) {
        std::copy(std::istreambuf_iterator<char>(stream),
                  std::istreambuf_iterator<char>(), addresses.begin() + 0x200);
    } else {
        std::cerr << "Failed to read file" << std::endl;
    }
}

void Memory::push(std::uint16_t address) { stack.push(address); }

std::uint16_t Memory::pop() {
    auto address = stack.top();
    stack.pop();
    return address;
}

void Memory::loadFont(const Font &font) {
    for (std::uint32_t i = 0; i < font.getSize(); i++) {
        auto character = font.getCharacter(i);
        std::copy(character.begin(), character.end(),
                  addresses.begin() + (i * font.getHeight()));
    }
}
