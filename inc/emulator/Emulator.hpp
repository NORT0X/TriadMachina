#include "../../inc/common/Elf.hpp"
#include "../../inc/emulator/Memory.hpp"
#include "../../inc/emulator/CPU.hpp"

#include <string>

class Emulator
{
    friend class CPU;

public:
    Emulator(std::string inputFile);

    void run();

private:
    Memory memory;
    CPU cpu;
};