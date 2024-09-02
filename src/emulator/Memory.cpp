#include "../../inc/emulator/Memory.hpp"

uint8_t Memory::read(Address address)
{
    return memory[address];
}

void Memory::write(Address address, uint8_t data)
{
    memory[address] = data;
}

uint32_t Memory::read32(Address address)
{
    uint32_t res = 0;

    for (int i = 0; i < 4; ++i)
    {
        res |= memory[address + i] << 8 * i;
    }

    return res;
}

void Memory::write32(Address address, uint32_t data)
{
    for (int i = 0; i < 4; ++i)
    {
        memory[address + i] = (data >> 8 * i) & 0xFF;
    }
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
