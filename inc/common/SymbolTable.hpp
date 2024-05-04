#include <vector>
#include <cstdint>

struct SymbolEntry;

typedef uint32_t SymbolIndex;

class SymbolTable
{
public:
    SymbolTable() {}

    void addSymbol(SymbolEntry entry);

    SymbolEntry *findSymbol(SymbolIndex index);

private:
    std::vector<SymbolEntry> table;
};
