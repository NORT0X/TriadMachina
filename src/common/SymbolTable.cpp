#include "../../inc/common/SymbolTable.hpp"

#include "../../inc/common/Elf.hpp"

#include <algorithm>
#include <iostream>

void SymbolTable::addSymbol(SymbolEntry entry, std::string name)
{
    // Add name to symbolNames vector and push index
    if (std::find(this->symbolNames.begin(), this->symbolNames.end(), name) != this->symbolNames.end())
    {
        // TODO: error occured
        std::cerr << "Error: Symbol already exists with name: " << name << std::endl;
    }

    StringIndex index = this->symbolNames.size();
    this->symbolNames.push_back(name);

    SymbolEntry updatedEntry(index, entry.section_id, entry.bind, entry.value, entry.defined, entry.flink);

    updatedEntry.index = this->id++;
    table.emplace_back(updatedEntry);
}

SymbolEntry *SymbolTable::findSymbol(std::string name)
{
    // Find the name in the symbolNames vector
    auto it = std::find(symbolNames.begin(), symbolNames.end(), name);

    // If the name is found
    if (it != symbolNames.end())
    {
        // Calculate the index of the found name
        StringIndex index = std::distance(symbolNames.begin(), it);

        // Check if the index is within the bounds of the table
        if (index < table.size())
        {
            return &table[index];
        }
        else
        {
            std::cerr << "Symbol index out of bounds: " << index << std::endl;
        }
    }

    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const SymbolTable &symbolTable)
{
    os << std::left
       << std::setw(20) << "Name"
       << std::setw(10) << "Index"
       << std::setw(10) << "Section"
       << std::setw(10) << "Bind"
       << std::setw(10) << "Value"
       << std::setw(10) << "Defined"
       << std::setw(10) << "Forward Ref"
       << '\n';

    for (size_t i = 0; i < symbolTable.table.size(); ++i)
    {
        const SymbolEntry &entry = symbolTable.table[i];
        os << std::setw(20) << symbolTable.symbolNames[i]
           << std::setw(10) << entry.index
           << std::setw(10) << entry.section_id
           << std::setw(10) << static_cast<int>(entry.bind)
           << std::setw(10) << entry.value
           << std::setw(10) << (entry.defined ? "Yes" : "No")
           << std::setw(10) << entry.flink
           << '\n';
    }

    return os;
}

std::vector<char> SymbolTable::getWriteData()
{
    std::vector<char> data;

    // Process each SymbolEntry in the table
    for (const SymbolEntry &entry : table)
    {
        // Write each attribute of SymbolEntry as 4 bytes (uint32_t)
        auto write_uint32 = [&data](uint32_t value)
        {
            data.push_back(static_cast<char>(value & 0xFF));
            data.push_back(static_cast<char>((value >> 8) & 0xFF));
            data.push_back(static_cast<char>((value >> 16) & 0xFF));
            data.push_back(static_cast<char>((value >> 24) & 0xFF));
        };

        write_uint32(entry.index);
        write_uint32(entry.name);
        write_uint32(entry.section_id);
        write_uint32(static_cast<uint32_t>(entry.bind));
        write_uint32(entry.value);
        write_uint32(static_cast<uint32_t>(entry.defined));
        write_uint32(entry.flink);
    }

    // Process each string in symbolNames
    for (const std::string &name : symbolNames)
    {
        // Write each character of the string as a byte
        data.insert(data.end(), name.begin(), name.end());

        // Null-terminate the string
        data.push_back('\0');
    }

    return data;
}