#include "../../inc/common/SectionTable.hpp"

#include "../../inc/common/Elf.hpp"

void SectionTable::addSection(SectionEntry section)
{
    this->table.emplace_back(section);
}

SectionEntry *SectionTable::findSection(SectionIndex index)
{
    for (SectionEntry &sec : this->table)
    {
        if (sec.index == index)
        {
            return &sec;
        }
    }

    return nullptr;
}