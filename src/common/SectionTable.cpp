#include "../../inc/common/SectionTable.hpp"

#include "../../inc/common/Elf.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>

void SectionTable::addSection(SectionEntry section, std::string name)
{
    if (std::find(this->sectionNames.begin(), this->sectionNames.end(), name) != this->sectionNames.end())
    {
        // TODO: error occured
        std::cerr << "Error: Symbol already exists with name: " << name << std::endl;
    }

    StringIndex index = this->sectionNames.size();
    this->sectionNames.push_back(name);

    SectionEntry updatedEntry(index, section.base, section.size);

    updatedEntry.index = this->id++;
    this->table.emplace_back(updatedEntry);
}

SectionEntry *SectionTable::findSection(std::string name)
{
    auto it = std::find(sectionNames.begin(), sectionNames.end(), name);

    // If the name is found
    if (it != sectionNames.end())
    {
        // Calculate the index of the found name
        StringIndex index = std::distance(sectionNames.begin(), it);

        // Check if the index is within the bounds of the table
        if (index < table.size())
        {
            return &table[index];
        }
        else
        {
            std::cerr << "Section index out of bounds: " << index << std::endl;
        }
    }

    return nullptr;
}

SectionEntry *SectionTable::findSection(SectionIndex index)
{
    if (index < table.size())
    {
        return &table[index];
    }
    else
    {
        std::cerr << "Section index out of bounds: " << index << std::endl;
    }

    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const SectionTable &sectionTable)
{
    os << std::left
       << std::setw(20) << "SectionName"
       << std::setw(10) << "Index"
       << std::setw(10) << "Base"
       << std::setw(10) << "Size"
       << '\n';

    for (size_t i = 0; i < sectionTable.table.size(); ++i)
    {
        const SectionEntry &entry = sectionTable.table[i];
        os << std::setw(20) << sectionTable.sectionNames[i]
           << std::setw(10) << entry.index
           << std::setw(10) << entry.base
           << std::setw(10) << entry.size
           << '\n';
    }

    return os;
}