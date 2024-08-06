#pragma once

#include <vector>
#include <cstdint>

struct RelaEntry;

typedef uint32_t SymbolIndex;

class RelaTable
{
public:
    void addEntry(RelaEntry entry);
    RelaEntry *getEntryForSymbol(SymbolIndex symbol_id);

private:
    std::vector<RelaEntry> table;
    uint32_t id = 0;
};