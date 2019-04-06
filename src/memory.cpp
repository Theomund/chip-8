#include "memory.h"

Memory::Memory() : addresses{} {}

std::uint8_t Memory::getAddress(const std::uint16_t index) const {
    return addresses.at(index);
}

void Memory::setAddress(const std::uint16_t index, const std::uint8_t value) {
    addresses.at(index) = value;
}

void Memory::loadROM(const std::string &name) {
    std::ifstream stream(name, std::ios::binary | std::ios::in);
    std::copy(std::istreambuf_iterator<char>(stream),
              std::istreambuf_iterator<char>(), addresses.begin() + 0x200);
}

void Memory::push(std::uint16_t address) { stack.push(address); }

std::uint16_t Memory::pop() {
    auto address = stack.top();
    stack.pop();
    return address;
}

void Memory::loadFont(const Font &font) {
    auto characters = font.getCharacters();
    for (auto character : characters) {
        std::copy(character.begin(), character.end(), addresses.begin());
    }
}
