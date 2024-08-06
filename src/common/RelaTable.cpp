#include "../../inc/common/RelaTable.hpp"
#include "../../inc/common/Elf.hpp"

#include <algorithm>

void RelaTable::addEntry(RelaEntry entry)
{
    this->table.emplace_back(entry);
}

RelaEntry *RelaTable::getEntryForSymbol(SymbolIndex id)
{
    for (RelaEntry &curr : this->table)
    {
        if (curr.symbol_id == id)
        {
            return &curr;
        }
    }

    return nullptr;
}