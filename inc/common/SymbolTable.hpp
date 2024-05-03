#include "Elf.hpp"
#include <vector>

class SymbolTable {
public:
    SymbolTable() { }

    bool insertSymbol(SymbolEntry entry);

    SymbolEntry getSymbolByIndex(SymbolIndex index);

private:
    std::vector<SymbolEntry> table;
};
