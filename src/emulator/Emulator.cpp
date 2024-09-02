#include "../../inc/emulator/Emulator.hpp"

#include <iostream>

Emulator::Emulator(std::string inputFile)
{
    ElfFile eFile;

    eFile.openForRead(inputFile);

    std::vector<char> codeBuffer = eFile.read();

    for (int i = 0; i < codeBuffer.size(); i += 5)
    {
        Address addr = (codeBuffer[i] << 8 * 3) |
                       (codeBuffer[i + 1] << 8 * 2) |
                       (codeBuffer[i + 2] << 8 * 1) |
                       (codeBuffer[i + 3]);

        uint8_t data = static_cast<uint8_t>(codeBuffer[i + 4]);

        this->memory.write(addr, data);
    }
}

void Emulator::run()
{
    // std::cout << this->memory;
}