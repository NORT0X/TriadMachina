#include "../../inc/linker/Linker.hpp"

void Linker::addInputFile(std::string fileName)
{
    this->inputFiles.push_back(fileName);
}

void Linker::addPlace(std::string section, Address address)
{
    this->placeArguments[section] = address;
}

void Linker::run()
{
    // Parse all Object files
    for (std::string &file : inputFiles)
    {
        this->loadObjectFromFile(file);
    }

    if (isHex && isRelocatable)
    {
        std::cerr << "Can't use -hex and -relocatable at the same time.\n";
        return;
    }

    if (isHex)
    {
        this->makeHexFile();
        return;
    }

    if (isRelocatable)
    {
        this->makeRelocatableFile();
        return;
    }
}

void Linker::loadObjectFromFile(std::string fileName)
{
    Object obj(fileName);
}