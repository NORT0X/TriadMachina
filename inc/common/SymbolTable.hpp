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
    std::string getSymbolName(SymbolIndex index) { return this->symbolNames[index]; };

    std::vector<char> getWriteData();

    void readFromData(const std::vector<char> &data);

    size_t getSize() const { return this->table.size(); }

    std::vector<SymbolEntry> getTable() const { return this->table; }
    bool checkAllDefined() const;

    friend std::ostream &operator<<(std::ostream &os, const SymbolTable &symbolTable);

private:
    std::vector<SymbolEntry> table;
    SymbolIndex id = 0;
    std::vector<std::string> symbolNames;
};
