#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

struct RelaEntry;

typedef uint32_t SymbolIndex;

class RelaTable
{
public:
    void addEntry(RelaEntry entry);
    RelaEntry *getEntryForSymbol(SymbolIndex symbol_id);
    size_t getSize() const { return this->table.size(); }

    std::vector<char> getWriteData() const;

    friend std::ostream &operator<<(std::ostream &os, const RelaTable &relaTable);

private:
    std::vector<RelaEntry> table;
    uint32_t id = 0;
};