#include <vector>
#include <cstdint>

struct LiteralEntry;

typedef uint32_t StringIndex;

class LiteralTable
{
public:
    LiteralTable() {}
    uint32_t addLiteral(LiteralEntry literal); // returns offset inside pool
    LiteralEntry *findLiteral(StringIndex index);
    void clear();
    std::vector<char> getWriteData();

    size_t getSizeInBytes() const { return table.size() * 4; }

private:
    std::vector<LiteralEntry> table;
};