#include "../../inc/emulator/Emulator.hpp"

#include <iostream>

Emulator::Emulator(std::string inputFile)
{
    ElfFile eFile;

    eFile.openForRead(inputFile);

    std::vector<char> codeBuffer = eFile.read();
    int counter = 0;
    for (int i = 0; i < codeBuffer.size(); i += 5)
    {
        counter++;
        Address addr = (static_cast<uint32_t>(static_cast<uint8_t>(codeBuffer[i])) << 8 * 3) |
                       (static_cast<uint32_t>(static_cast<uint8_t>(codeBuffer[i + 1])) << 8 * 2) |
                       (static_cast<uint32_t>(static_cast<uint8_t>(codeBuffer[i + 2])) << 8 * 1) |
                       (static_cast<uint32_t>(static_cast<uint8_t>(codeBuffer[i + 3])));

        uint8_t data = static_cast<uint8_t>(codeBuffer[i + 4]);

        this->memory.write(addr, data);
    }

    cpu.attachMemory(&memory);
}

void Emulator::run()
{
    cpu.reset();
    cpu.start();

    while (cpu.isRunning())
    {
        cpu.tick();
    }
    std::cout << cpu;
    // std::cout << memory;
}