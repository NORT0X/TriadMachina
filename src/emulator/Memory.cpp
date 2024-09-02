#include "../../inc/emulator/Memory.hpp"

uint8_t Memory::read(Address address)
{
    return this->memory[address];
}

void Memory::write(Address address, uint8_t data)
{
    this->memory[address] = data;
}

std::ostream &operator<<(std::ostream &os, const Memory &memory)
{
    os << "\n\nMemory\n";

    for (const auto &pair : memory.memory)
    {
        os << std::hex << std::uppercase << pair.first << ": " << static_cast<unsigned int>(pair.second) << '\n';
    }

    os << std::dec;

    return os;
}
