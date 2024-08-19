#pragma once

#include "../common/Elf.hpp"
#include "../linker/Object.hpp"

#include <vector>
#include <map>
#include <string>

class Object;

class Linker
{
public:
    Linker() : isHex(false), isRelocatable(false) {}

    void addInputFile(std::string fileName);
    void setHex() { this->isHex = true; }
    void setRelocatable() { this->isRelocatable = true; }
    void addPlace(std::string section, Address address);

    void run();

    void loadObjectFromFile(std::string fileName);

    void makeHexFile();
    void makeRelocatableFile();

private:
    std::string outFile;

    std::vector<std::string> inputFiles;

    std::map<std::string, Address> placeArguments;
    bool isHex;
    bool isRelocatable;

    std::vector<Object> objects;
};