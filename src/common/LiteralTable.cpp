#include "../../inc/common/LiteralTable.hpp"

#include "../../inc/common/Elf.hpp"

void LiteralTable::addLiteral(LiteralEntry literal)
{
    this->table.emplace_back(literal);
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
