#pragma once

#include "../common/Elf.hpp"
#include "../linker/Object.hpp"

#include <vector>
#include <map>
#include <set>
#include <string>

class Object;

enum class OutType
{
    HEX,
    RELOCATABLE
};

class Linker
{
public:
    Linker() : isHex(false), isRelocatable(false) {}

    void setOutputFile(std::string fileName) { this->outFileName = fileName; }
    void addInputFile(std::string fileName);
    void setHex() { this->isHex = true; }
    void setRelocatable() { this->isRelocatable = true; }
    void addPlace(std::string section, Address address);

    void run();

    void loadObjectFromFile(std::string fileName);

    void makeHexFile();
    void makeRelocatableFile();
    void writeSection(std::string section, OutType type);
    void fixRelocations();
    void writeBinaryHex();
    void writeRelocatableElf();
    void writeHeaderAndTables();

private:
    std::string outFileName;
    ElfFile outFile;

    std::map<Address, char> code;
    std::set<std::string> finishedSec;

    std::vector<std::string> inputFiles;

    std::map<std::string, Address> placeArguments;
    Address currPosition = 0;

    bool isHex;
    bool isRelocatable;

    std::vector<Object> objects;

    SectionTable secTable;
    SymbolTable symTable;
    RelaTable relaTable;
};