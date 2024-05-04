#include "../../inc/common/SymbolTable.hpp"

#include "../../inc/common/Elf.hpp"

void SymbolTable::addSymbol(SymbolEntry entry)
{
    table.emplace_back(entry);
}

SymbolEntry *SymbolTable::findSymbol(SymbolIndex index)
{
    for (SymbolEntry &sym : this->table)
    {
        if (sym.index == index)
        {
            return &sym;
        }
    }
    return nullptr;
}