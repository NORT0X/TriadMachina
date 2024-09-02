#include "../../inc/common/Elf.hpp"
#include "../../inc/emulator/Memory.hpp"

#include <string>

class Emulator
{
public:
    Emulator(std::string inputFile);

    void run();

private:
    Memory memory;
};