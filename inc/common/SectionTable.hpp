#include <vector>
#include <cstdint>
#include <string>

struct SectionEntry;

typedef uint32_t SectionIndex;

class SectionTable
{
public:
    void addSection(SectionEntry section, std::string name);
    SectionEntry *findSection(std::string name);
    SectionEntry *findSection(SectionIndex index);

    int tableSize() const { return this->table.size(); }

    friend std::ostream &operator<<(std::ostream &os, const SectionTable &sectionTable);

private:
    std::vector<SectionEntry> table;
    SectionIndex id = 0;
    std::vector<std::string> sectionNames;
};