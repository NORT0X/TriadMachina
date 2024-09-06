#pragma once

#include "../common/Elf.hpp"

#include <map>
#include <cstdint>

class Memory
{
public:
    Memory() {}

    uint8_t read(Address address);
    void write(Address address, uint8_t data);

    uint32_t read32(Address address);
    void write32(Address address, uint32_t data);

    bool isTermOUT() const { return writenToTermOUT; }
    void resetTermOUT() { writenToTermOUT = false; }

    friend std::ostream &operator<<(std::ostream &os, const Memory &memory);

private:
    std::map<Address, uint8_t> memory;

    bool writenToTermOUT = false;
};