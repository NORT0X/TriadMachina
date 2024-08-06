#include "../../inc/assembler/Assembler.hpp"
#include "../../inc/common/Elf.hpp"

#include <iostream>

void Assembler::addFlinkForSymbol(std::string symbolName, uint32_t position)
{
    // Check if symbol exists and if is not defined
    // If it doesn't exists create new undefined symbol

    SymbolEntry *entry = this->symbolTable.findSymbol(symbolName);

    if (entry != nullptr && entry->defined == false && entry->bind != SymbolBind::EXTERN_BIND)
    {
        // Add flink
        ForwardRefEntry flink(this->forwardRefs.size(), position);
        this->forwardRefs.emplace_back(flink);

        // If flink already exists add it to the end
        uint32_t prev = -1;
        uint32_t index = entry->flink;
        while (index < this->forwardRefs.size())
        {
            ForwardRefEntry *curr = &this->forwardRefs[index];
            prev = index;
            index = curr->next;
        }

        if (prev < this->forwardRefs.size())
        {
            // Already exists some flinks for this symbol
            this->forwardRefs[prev].next = flink.index;
        }
        else
        {
            // This is first flink for this symbol
            entry->flink = flink.index;
        }
    }

    if (entry == nullptr)
    {
        // Addd symbol and flink for it
        ForwardRefEntry flink(this->forwardRefs.size(), position);
        this->forwardRefs.emplace_back(flink);

        SymbolEntry newEntry(0, 0, SymbolBind::LOCAL_BIND, 0, false, flink.index);
        this->symbolTable.addSymbol(newEntry, symbolName);
    }

    // After this maybe symbol is extern which means that linker should fix and not assembler backpatching
}

void Assembler::patchFlinksForSymbol(std::string symbolName)
{
    std::cout << "test\n";
    SymbolEntry *symEntry = this->symbolTable.findSymbol(symbolName);

    std::vector<char> buff(4, 0);
    buff[0] = symEntry->value >> 8 * 3;
    buff[1] = symEntry->value >> 8 * 2;
    buff[2] = symEntry->value >> 8 * 1;
    buff[3] = symEntry->value;

    uint32_t prev = -1;
    uint32_t index = symEntry->flink;
    while (index < this->forwardRefs.size())
    {
        ForwardRefEntry *curr = &this->forwardRefs[index];
        this->eFile.writeAtPosition(curr->patch, buff);
        index = curr->next;
    }
}

void Assembler::poolPatching()
{
    for (const auto &pair : poolBackpatch)
    {
        std::cout << "POOLBACKPATCH\n";
        uint32_t position = pair.first;
        uint32_t offsetInPool = pair.second;

        SectionEntry *section = this->sectionTable.findSection(this->currentSection);
        uint32_t sectionPosition = position - section->base + 2;
        uint32_t offset = section->size + offsetInPool - sectionPosition;

        if (offset > 0x0FFF)
        {
            std::cerr << "warning: pool goes out of bounds.";
        }
        std::vector<char> buff(2, 0);
        buff[0] = offset >> 8;
        buff[1] = offset;
        std::cout << position << '\n';

        this->eFile.writeAtPosition(position, buff);
    }
}