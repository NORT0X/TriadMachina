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

    write_uint32(this->table.size());

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

void SectionTable::readFromData(const std::vector<char> &data)
{
    size_t offset = 0;

    auto read_uint32 = [&data, &offset]() -> uint32_t
    {
        uint32_t value = 0;
        value |= static_cast<uint8_t>(data[offset]);
        value |= static_cast<uint8_t>(data[offset + 1]) << 8;
        value |= static_cast<uint8_t>(data[offset + 2]) << 16;
        value |= static_cast<uint8_t>(data[offset + 3]) << 24;
        offset += sizeof(uint32_t);
        return value;
    };

    // Clear the current symbol table and names
    table.clear();
    sectionNames.clear();
    id = 0; // reset the symbol index counter

    uint32_t num_sections = read_uint32();

    // Read SymbolEntries
    while (offset < num_sections * 16)
    {

        // Try reading each field assuming we are still in the symbol entries section
        SectionEntry entry(-1, 0, 0);

        try
        {
            entry.index = read_uint32();
            entry.name = read_uint32();
            entry.base = read_uint32();
            entry.size = read_uint32();
        }
        catch (const std::out_of_range &)
        {
            break; // Exit loop if we run out of data (in case of incomplete data)
        }

        table.push_back(entry);

        // Update the id to track the last symbol index
        id = entry.index + 1;
    }

    // Read symbol names
    while (offset < data.size())
    {
        std::string name;

        // Extract characters from data until we hit the null terminator
        while (offset < data.size() && data[offset] != '\0')
        {
            name.push_back(data[offset]);
            ++offset;
        }

        // Skip the null terminator
        if (offset < data.size() && data[offset] == '\0')
        {
            ++offset;
        }

        // Add the string to the symbol names list
        sectionNames.push_back(name);
    }
}