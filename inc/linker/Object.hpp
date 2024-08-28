#pragma once

#include "../common/SymbolTable.hpp"
#include "../common/SectionTable.hpp"
#include "../common/RelaTable.hpp"

#include "../common/Elf.hpp"

class Object
{
    friend class Linker;

public:
    Object(std::string fileName);

    void loadObjectFile();
    void loadHeader();
    void loadCode();

private:
    ElfFile eFile;
    ObjectHeader header;

    SymbolTable symbolTable;
    SectionTable sectionTable;
    RelaTable relaTable;

    std::vector<char> code; // header->codeStart is start address (no need for map)
};
