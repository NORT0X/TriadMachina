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

    Emulator emulator(argv[1]);

    emulator.run();

    return 0;
}