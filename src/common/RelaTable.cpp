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