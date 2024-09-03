#include "../../inc/emulator/Emulator.hpp"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "No input file specified.\n";
        return -2;
    }

    std::string inputFile = argv[1];

    Emulator emulator(inputFile);

    emulator.run();

    return 0;
}