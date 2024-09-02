#include "../../inc/common/Elf.hpp"

class Memory;

#include <cstdint>

class CPU
{
public:
    CPU();

    void reset();
    void start() { this->running = true; }
    void attachMemory(Memory *memory) { this->memory = memory; }

    void fetch();
    void execute();

    void push(uint32_t reg);
    uint32_t pop();

private:
    void callInstr();
    void jmpInstr();
    void arithmeticInstr();
    void logicInstr();
    void loadInstr();
    void storeInstr();

private:
    uint8_t IR[4];
    MInstruction currentInstruction;
    uint32_t GPR[16];
    uint32_t CSR[3];

    bool running = false;

    Memory *memory;
};