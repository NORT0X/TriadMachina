#include "../../inc/common/LiteralTable.hpp"

#include "../../inc/common/Elf.hpp"

uint32_t LiteralTable::addLiteral(LiteralEntry literal)
{
    // If it's zero value then just add it because that's for rela
    if (literal.value == 0)
    {
        this->table.emplace_back(literal);
        return (4 * (this->table.size() - 1));
    }

    // find if there is already literal with same value inside pool
    for (int i = 0; i < this->table.size(); ++i)
    {
        if (this->table[i].value == literal.value)
        {
            return i * 4;
        }
    }

    this->table.emplace_back(literal);
    return (4 * (this->table.size() - 1));
}

LiteralEntry *LiteralTable::findLiteral(StringIndex index)
{
    for (LiteralEntry &literal : this->table)
    {
        if (literal.index == index)
        {
            return &literal;
        }
    }

    return nullptr;
}

void LiteralTable::clear()
{
    this->table.clear();
}

std::vector<char> LiteralTable::getWriteData()
{
    std::vector<char> res;
    for (LiteralEntry &entry : this->table)
    {
        res.emplace_back((char)(entry.value >> 8 * 3));
        res.emplace_back((char)(entry.value >> 8 * 2));
        res.emplace_back((char)(entry.value >> 8));
        res.emplace_back((char)entry.value);
    }
    return res;
}