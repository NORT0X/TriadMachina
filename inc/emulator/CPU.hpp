#include "../../inc/common/Elf.hpp"

class Memory;

#include <cstdint>

enum class INT_CAUSE
{
    BAD_INSTR = 1,
    TIMER,
    TERMINAL,
    SOFTWARE
};

class CPU
{
public:
    friend class Emulator;
    CPU();

    void reset();
    void start() { this->running = true; }
    bool isRunning() const { return this->running; }
    void attachMemory(Memory *memory) { this->memory = memory; }

    void tick();

    void fetch();
    void execute();
    void interruptHandler();

    void push(uint32_t reg);
    uint32_t pop();

    friend std::ostream &operator<<(std::ostream &os, const CPU &cpu);

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