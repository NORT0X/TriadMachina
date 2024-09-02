#include "../common/Elf.hpp"

#include <map>
#include <cstdint>

class Memory
{
public:
    Memory() {}

    uint8_t read(Address address);
    void write(Address address, uint8_t data);

    friend std::ostream &operator<<(std::ostream &os, const Memory &memory);

private:
    std::map<Address, uint8_t> memory;
};