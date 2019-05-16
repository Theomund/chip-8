#include "memory.h"
#include <iostream>

Memory::Memory() : addresses{} {}

unsigned char Memory::getAddress(const unsigned int index) const
{
    return static_cast<unsigned char>(addresses.at(index));
}

void Memory::setAddress(const unsigned int index, const unsigned char value)
{
    addresses.at(index) = value;
}

void Memory::loadROM(const std::string &name)
{
    std::ifstream stream(name, std::ios::binary | std::ios::in);
    if (stream.is_open())
    {
        std::copy(std::istreambuf_iterator<char>(stream),
                  std::istreambuf_iterator<char>(), addresses.begin() + 0x200);
    }
    else
    {
        throw std::runtime_error("Failed to read file");
    }
}

void Memory::push(unsigned short address) { stack.push(address); }

unsigned short Memory::pop()
{
    auto address = stack.top();
    stack.pop();
    return address;
}

void Memory::loadFont(const Font &font)
{
    for (size_t i = 0; i < font.getSize(); i++)
    {
        auto character = font.getCharacter(i);
        std::copy(character.begin(), character.end(),
                  addresses.begin() + (i * font.getHeight()));
    }
}
