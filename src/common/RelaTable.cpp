#include "../../inc/common/RelaTable.hpp"
#include "../../inc/common/Elf.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>

void RelaTable::addEntry(RelaEntry entry)
{
    this->table.emplace_back(entry);
}

RelaEntry *RelaTable::getEntryForSymbol(SymbolIndex id)
{
    for (RelaEntry &curr : this->table)
    {
        if (curr.symbol_id == id)
        {
            return &curr;
        }
    }

    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const RelaTable &relaTable)
{
    os << std::left
       << std::setw(20) << "offset"
       << std::setw(10) << "SecID"
       << std::setw(10) << "type"
       << std::setw(10) << "SymID"
       << std::setw(10) << "addend"
       << '\n';

    for (size_t i = 0; i < relaTable.table.size(); ++i)
    {
        const RelaEntry &entry = relaTable.table[i];
        os << std::setw(20) << entry.offset
           << std::setw(10) << entry.section_id
           << std::setw(10) << (entry.type == RelaType::ABS ? "ABS" : "PC_REL")
           << std::setw(10) << entry.symbol_id
           << std::setw(10) << entry.addend
           << '\n';
    }

    return os;
}

std::vector<char> RelaTable::getWriteData() const
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
    for (const RelaEntry &entry : table)
    {
        write_uint32(entry.offset);
        write_uint32(entry.section_id);
        write_uint32(entry.type);
        write_uint32(entry.symbol_id);
        write_uint32(entry.addend);
    }

    return data;
}

void RelaTable::readFromData(const std::vector<char> &data)
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
    id = 0; // reset the symbol index counter

    // Read SymbolEntries
    while (offset < data.size())
    {

        // Try reading each field assuming we are still in the symbol entries section
        RelaEntry entry(-1, -1, RelaType::ABS, -1, -1);

        try
        {
            entry.offset = read_uint32();
            entry.section_id = read_uint32();
            entry.type = static_cast<RelaType>(read_uint32());
            entry.symbol_id = read_uint32();
            entry.addend = read_uint32();
        }
        catch (const std::out_of_range &)
        {
            break; // Exit loop if we run out of data (in case of incomplete data)
        }

        table.push_back(entry);

        // Update the id to track the last symbol index
    }
}