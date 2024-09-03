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
    // Also this only makes sense if symbol somehow is not label (because label has memory value)
    SymbolEntry *symEntry = this->symbolTable.findSymbol(symbolName);

    std::vector<char> buff(4, 0);
    buff[0] = symEntry->value >> 8 * 3;
    buff[1] = symEntry->value >> 8 * 2;
    buff[2] = symEntry->value >> 8 * 1;
    buff[3] = symEntry->value;

    uint32_t index = symEntry->flink;
    while (index < this->forwardRefs.size())
    {

        ForwardRefEntry *curr = &this->forwardRefs[index];

        // Read current value from file at the patch position
        std::vector<char> currentValue(4, 0);
        if (!this->eFile.readAtPosition(curr->patch, currentValue, 4))
        {
            std::cerr << "Failed to read current value at position: " << curr->patch << std::endl;
            return;
        }

        // Convert current value from vector<char> to uint32_t
        uint32_t currentVal = (static_cast<uint32_t>(currentValue[0]) << 24) |
                              (static_cast<uint32_t>(currentValue[1]) << 16) |
                              (static_cast<uint32_t>(currentValue[2]) << 8) |
                              static_cast<uint32_t>(currentValue[3]);

        // Perform the bitwise OR operation
        uint32_t newVal = currentVal | symEntry->value;

        // Prepare the new value as a 4-byte vector
        std::vector<char> newBuff(4, 0);
        newBuff[0] = newVal >> 24;
        newBuff[1] = newVal >> 16;
        newBuff[2] = newVal >> 8;
        newBuff[3] = newVal;

        // Write the new value back to the file
        if (!this->eFile.writeAtPosition(curr->patch, newBuff))
        {
            std::cerr << "Failed to write new value at position: " << curr->patch << std::endl;
            return;
        }

        index = curr->next;
    }
}

void Assembler::poolPatching()
{
    for (const auto &pair : poolBackpatch)
    {
        uint32_t position = pair.first;
        uint32_t offsetInPool = pair.second;

        SectionEntry *section = this->sectionTable.findSection(this->currentSection);
        uint32_t sectionPosition = position - section->base + 4;
        uint32_t offset = section->size + offsetInPool - sectionPosition;

        if (offset > 0x0FFF)
        {
            std::cerr << "warning: pool goes out of bounds.";
        }

        // Read current value from file at the patch position
        std::vector<char> currentValue(2, 0);
        if (!this->eFile.readAtPosition(position, currentValue, 2))
        {
            std::cerr << "Failed to read current value at position: " << position << std::endl;
            return;
        }

        // Convert current value from vector<char> to uint32_t
        uint32_t currentVal = (static_cast<uint32_t>(currentValue[1]) << 8) |
                              static_cast<uint32_t>(currentValue[0]);

        uint16_t actualOffset = currentVal | offset;

        std::vector<char> buff(2, 0);
        buff[1] = actualOffset >> 8;
        buff[0] = actualOffset;

        this->eFile.writeAtPosition(position, buff);
    }
}

void Assembler::addAbsRela(std::string symbol)
{
    SymbolEntry *sym = this->symbolTable.findSymbol(symbol);
    RelaEntry entry(this->locationCounter, this->currentSection, RelaType::ABS, sym->index, 0);
    this->relaTable.addEntry(entry);
}