#include <vector>
#include <cstdint>

struct LiteralEntry;

typedef uint32_t StringIndex;

class LiteralTable
{
public:
    void addLiteral(LiteralEntry literal);
    LiteralEntry *findLiteral(StringIndex index);

private:
    std::vector<LiteralEntry> table;
};