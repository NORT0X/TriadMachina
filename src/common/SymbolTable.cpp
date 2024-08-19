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

    auto write_uint32 = [&data](uint32_t value)
    {
        data.push_back(static_cast<char>(value & 0xFF));
        data.push_back(static_cast<char>((value >> 8) & 0xFF));
        data.push_back(static_cast<char>((value >> 16) & 0xFF));
        data.push_back(static_cast<char>((value >> 24) & 0xFF));
    };

    write_uint32(this->table.size());

    // Process each SymbolEntry in the table
    for (const SymbolEntry &entry : table)
    {
        // Write each attribute of SymbolEntry as 4 bytes (uint32_t)

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

void SymbolTable::readFromData(const std::vector<char> &data)
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
    symbolNames.clear();
    id = 0; // reset the symbol index counter

    uint32_t num_symbols = read_uint32();

    // Read SymbolEntries
    while (offset < num_symbols * 28)
    {

        // Try reading each field assuming we are still in the symbol entries section
        SymbolEntry entry(-1, -1, SymbolBind::UND, 0);

        try
        {
            entry.index = read_uint32();
            entry.name = read_uint32();
            entry.section_id = read_uint32();
            entry.bind = static_cast<SymbolBind>(read_uint32());
            entry.value = read_uint32();
            entry.defined = static_cast<bool>(read_uint32());
            entry.flink = read_uint32();
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
        symbolNames.push_back(name);
    }
}