#include "../../inc/linker/Linker.hpp"

#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>
#include <memory>

int main(int argc, char *argv[])
{
    std::string outputFile;
    std::unique_ptr<Linker> linker = std::make_unique<Linker>();

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-o" && i + 1 < argc)
        {
            outputFile = argv[++i];
            linker->setOutputFile(outputFile);
            continue;
        }

        const std::string prefix = "-place=";
        if (arg.rfind(prefix, 0) == 0)
        {
            // Extract the part after "–place="
            std::string section_and_address = arg.substr(prefix.length());
            std::cout << "TEST\n";
            // Split at '@'
            size_t at_pos = section_and_address.find('@');
            if (at_pos != std::string::npos)
            {
                std::string section = section_and_address.substr(0, at_pos);
                std::string address = section_and_address.substr(at_pos + 1);

                // Output the results
                uint32_t value = static_cast<uint32_t>(std::stoul(address, nullptr, 16));
                std::cout << section << " " << value << "\n";
                linker->addPlace(section, value);
            }

            else
            {
                std::cerr << "Invalid format. '@' symbol not found in argument.\n";
            }
            continue;
        }

        if (arg == "-hex")
        {
            linker->setHex();
            continue;
        }

        if (arg == "-relocatable")
        {
            linker->setRelocatable();
            continue;
        }

        linker->addInputFile(arg);
    }

    linker->run();

    return 0;
}