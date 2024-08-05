#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <iomanip>

struct SymbolEntry;

typedef uint32_t SymbolIndex;

class SymbolTable
{
public:
    SymbolTable() {}

    void addSymbol(SymbolEntry entry, std::string name);

    SymbolEntry *findSymbol(std::string name);

    friend std::ostream &operator<<(std::ostream &os, const SymbolTable &symbolTable);

private:
    std::vector<SymbolEntry> table;
    SymbolIndex id = 0;
    std::vector<std::string> symbolNames;
};
