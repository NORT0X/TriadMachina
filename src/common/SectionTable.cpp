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

std::vector<char> SectionTable::getWriteData() const
{
    std::vector<char> data;

    // Lambda to write a uint32_t value in big endian
    auto write_uint32 = [&data](uint32_t value)
    {
        data.push_back(static_cast<char>(value & 0xFF));
        data.push_back(static_cast<char>((value >> 8) & 0xFF));
        data.push_back(static_cast<char>((value >> 16) & 0xFF));
        data.push_back(static_cast<char>((value >> 24) & 0xFF));
    };

    // Process each SectionEntry in the table
    for (const SectionEntry &entry : table)
    {
        write_uint32(entry.index);
        write_uint32(entry.name); // Ensure name is an appropriate index or identifier
        write_uint32(static_cast<uint32_t>(entry.base));
        write_uint32(static_cast<uint32_t>(entry.size));
    }

    // Process each string in sectionNames
    for (const std::string &name : sectionNames)
    {
        // Write each character of the string as a byte
        data.insert(data.end(), name.begin(), name.end());

        // Null-terminate the string (if required by your format)
        data.push_back('\0');
    }

    return data;
}
