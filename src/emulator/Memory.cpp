#include "../../inc/emulator/Memory.hpp"

#include <iostream>

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
    if (address >= TERM_OUT && address < (TERM_OUT + 4))
    {
        this->writenToTermOUT = true;
    }

    for (int i = 0; i < 4; ++i)
    {
        memory[address + i] = (data >> 8 * i) & 0xFF;
    }
}

std::ostream &operator<<(std::ostream &os, const Memory &memory)
{
    os << "\n\nMemory\n";
    int i = 0;
    for (const auto &pair : memory.memory)
    {
        os << std::hex << std::uppercase;
        if (i == 4)
        {
            os << "\n"
               << pair.first << ": ";
            i = 0;
        }
        os << static_cast<unsigned int>(pair.second) << ' ';
        ++i;
    }

    os << std::dec << '\n';

    return os;
}
