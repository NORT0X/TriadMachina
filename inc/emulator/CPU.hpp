#include "../../inc/common/Elf.hpp"

class Memory;

#include <cstdint>

class CPU
{
public:
    CPU();

    void reset();
    void attachMemory(Memory *memory) { this->memory = memory; }

    void fetch();
    void execute();

private:
    uint8_t IR[4];
    MInstruction currentInstruction;
    uint32_t GPR[16];
    uint32_t status;
    uint32_t handler;
    uint32_t cause;

    Memory *memory;
};