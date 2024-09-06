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

    std::string getName(SectionIndex index) const { return this->sectionNames[index]; }

    int getSize() const { return this->table.size(); }
    std::vector<char> getWriteData() const;
    void readFromData(const std::vector<char> &data);

    std::vector<SectionEntry> getTable() const { return this->table; }

    friend std::ostream &operator<<(std::ostream &os, const SectionTable &sectionTable);

private:
    std::vector<SectionEntry> table;
    SectionIndex id = 0;
    std::vector<std::string> sectionNames;
};