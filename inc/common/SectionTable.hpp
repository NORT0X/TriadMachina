#include <vector>
#include <cstdint>

struct SectionEntry;

typedef uint32_t SectionIndex;

class SectionTable
{
public:
    void addSection(SectionEntry section);
    SectionEntry *findSection(SectionIndex index);

private:
    std::vector<SectionEntry> table;
};