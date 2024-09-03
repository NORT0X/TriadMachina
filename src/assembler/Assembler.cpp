#include "../../inc/assembler/Assembler.hpp"
#include "../../inc/common/Elf.hpp"

#include <iostream>
#include <bitset>

Assembler::Assembler(std::string outputFile) : outputFile(outputFile)
{
    this->eFile.open(outputFile);
    this->symbolTable = SymbolTable();
    this->sectionTable = SectionTable();

    // Reserve places at the beginning for three
    std::vector<char> buff(4, 0);
    for (int i = 0; i < 4 * 2; ++i)
    {
        this->eFile.write(buff);
        this->locationCounter += 4;
    }
}

void Assembler::end()
{
    // Update last section size and write pool
    if (this->sectionTable.getSize() > 0)
    {
        SectionEntry *lastSection = this->sectionTable.findSection(this->sectionTable.getSize() - 1);
        lastSection->size = this->locationCounter - lastSection->base;

        // Write pool
        this->eFile.write(this->currSecPool.getWriteData());

        // Size of pool to locationCounter
        this->locationCounter += this->currSecPool.getSizeInBytes();

        // Now add rela to fix pool where zeros are
        for (const auto &pair : this->poolZeroRela)
        {
            uint32_t offsetInPool = pair.first;
            SymbolIndex symbToRel = pair.second;

            RelaEntry newRela(offsetInPool + lastSection->size, this->currentSection, RelaType::ABS, symbToRel, 0);
            this->relaTable.addEntry(newRela);
        }

        // Do pool backpatching
        this->poolPatching();

        lastSection->size += this->currSecPool.getWriteData().size();
        this->poolBackpatch.clear(); // Delete map boolBackpatching

        this->currSecPool.clear();
    }

    // Print
    std::cout << "\n\nSymbolTable\n\n";
    std::cout << this->symbolTable;
    std::cout << "\n\nSectionTable\n\n";
    std::cout << this->sectionTable;
    std::cout << "\n\nRelaTable\n\n";
    std::cout << this->relaTable;

    this->writeHeaderAndTables(); // writeHeader must be called here
}

void Assembler::writeHeaderAndTables()
{

    // Write code size
    this->eFile.writeAtPosition(0, 32);
    this->eFile.writeAtPosition(4, this->locationCounter - 32);

    // Write symbol table info
    size_t tmp = this->eFile.getFileSize();
    this->eFile.writeAtPosition(8, tmp);
    this->eFile.write(this->symbolTable.getWriteData());
    this->eFile.writeAtPosition(12, this->eFile.getFileSize() - tmp);

    // Write section table info
    tmp = this->eFile.getFileSize();
    this->eFile.writeAtPosition(16, tmp);
    this->eFile.write(this->sectionTable.getWriteData());
    this->eFile.writeAtPosition(20, this->eFile.getFileSize() - tmp);

    // Write rela table info
    tmp = this->eFile.getFileSize();
    this->eFile.writeAtPosition(24, tmp);
    this->eFile.write(this->relaTable.getWriteData());
    this->eFile.writeAtPosition(28, this->eFile.getFileSize() - tmp);
}

void Assembler::skipDirective(uint32_t literal)
{
    locationCounter += literal;

    std::vector<char> buff(literal, 0);

    this->eFile.write(buff);
}

void Assembler::globalDirective(std::string name)
{
    // Check if symbol exists if not add him to table
    SymbolEntry *entry = this->symbolTable.findSymbol(name);

    if (entry != nullptr)
    {
        entry->bind = SymbolBind::GLOBAL_BIND;
    }
    else
    {
        SymbolEntry entry(0, currentSection, SymbolBind::GLOBAL_BIND, 0);
        this->symbolTable.addSymbol(entry, name);
        // Because this is still not defined it should be set
        // Flink also should not be defined since it's not exaclty used
    }
}

void Assembler::externDirective(std::string name)
{
    // Check if symbol exists if not add him to table
    SymbolEntry *entry = this->symbolTable.findSymbol(name);

    if (entry != nullptr)
    {
        entry->bind = SymbolBind::EXTERN_BIND;
    }
    else
    {
        SymbolEntry entry(0, currentSection, SymbolBind::EXTERN_BIND, 0);
        this->symbolTable.addSymbol(entry, name);
    }
}

void Assembler::sectionDirective(std::string sectionName)
{
    // Check if this section exists
    SectionEntry *entry = this->sectionTable.findSection(sectionName);

    // Before anything update size of previous section
    if (this->sectionTable.getSize() > 0)
    {
        SectionEntry *prevSection = this->sectionTable.findSection(currentSection);
        prevSection->size = this->locationCounter - prevSection->base;

        // Write current literal pool at the end of section and clear it for next
        std::vector<char> pool = this->currSecPool.getWriteData();
        this->eFile.write(pool);

        //  Add size of pool to locationCounter
        this->locationCounter += this->currSecPool.getSizeInBytes();

        // Now add rela to fix pool where zeros are
        for (const auto &pair : this->poolZeroRela)
        {
            uint32_t offsetInPool = pair.first;
            SymbolIndex symbToRel = pair.second;

            RelaEntry newRela(offsetInPool + prevSection->size, this->currentSection, RelaType::ABS, symbToRel, 0);
            this->relaTable.addEntry(newRela);
        }

        // Do pool backpatching
        this->poolPatching();

        prevSection->size += pool.size();
        this->poolBackpatch.clear(); // Delete map boolBackpatching
        this->poolZeroRela.clear();

        this->currSecPool.clear();
    }

    if (entry != nullptr)
    {
    }
    else
    {
        SectionEntry entry(0, this->locationCounter, 0);
        this->sectionTable.addSection(entry, sectionName);
        this->currentSection = this->sectionTable.findSection(sectionName)->index;

        // Create pool for this section (automaticlly)
    }
}

void Assembler::wordDirectiveLiteral(uint32_t literal)
{
    std::vector<char> buff(4, 0);

    buff[0] = literal >> 8 * 3;
    buff[1] = literal >> 8 * 2;
    buff[2] = literal >> 8;
    buff[3] = literal;

    this->eFile.write(buff);
    locationCounter += 4;
}

void Assembler::wordDirectiveSymbol(std::string symbolName)
{
    std::vector<char> buff(4, 0);

    SymbolEntry *entry = this->symbolTable.findSymbol(symbolName);

    // If entry doesn't exist add it and add rela
    if (entry == nullptr)
    {
        SymbolEntry newEntry(0, -1, SymbolBind::UND, 0);
        this->symbolTable.addSymbol(newEntry, symbolName);
        entry = this->symbolTable.findSymbol(symbolName);
    }

    this->addAbsRela(symbolName);

    this->eFile.write(buff);
    locationCounter += 4;
}

void Assembler::label(std::string labelName)
{
    // If it's already in symbol table update value
    SymbolEntry *exists = this->symbolTable.findSymbol(labelName);
    if (exists != nullptr && exists->defined == true)
    {
        std::cerr << "error: this symbol as label " << labelName << " is already defined\n";
        return;
    }

    if (exists != nullptr && exists->defined == false)
    {
        exists->value = this->locationCounter - this->sectionTable.findSection(currentSection)->base; // - 32 because of header
        exists->section_id = this->currentSection;
        exists->defined = true;
    }

    // If it's not already in symbol table that means that it's local variable
    if (exists == nullptr)
    {
        uint32_t value = this->locationCounter - this->sectionTable.findSection(currentSection)->base;
        SymbolEntry entry(0, this->currentSection, SymbolBind::LOCAL_BIND, value, true);
        this->symbolTable.addSymbol(entry, labelName);
    }

    // Backpatching
    this->patchFlinksForSymbol(labelName);
}

void Assembler::insertInstruction(MInstruction instruction, bool isLittleEndian)
{
    std::vector<char> buff(4, 0);

    buff[3] = static_cast<uint8_t>(instruction.OC) << 4 | (instruction.MOD & 0x0F);
    buff[2] = instruction.A << 4 | (instruction.B & 0x0F);
    buff[1] = instruction.C << 4 | (instruction.DISP >> 8 & 0x0F);
    buff[0] = instruction.DISP;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::jmpInstruction(uint32_t literal)
{
    if (literal <= 0x0FFF)
    {
        MInstruction instr(OPCODE::JMP, 0, 0, 0, 0, literal);
        this->insertInstruction(instr);
        return;
    }
    // In other case we have to put in literal pool for current section and that's it
    // And do pc <= mem32[pc + disp(sec_base + literal_pool + offset)]
    // Displacement should linker fix later

    // Add literal to pool
    LiteralEntry newLiteral(literal);

    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    // Write instruction
    MInstruction instr(OPCODE::JMP, 8, PC, 0, 0, 0);
    this->insertInstruction(instr);

    // Add backpatch for poolOffset
    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
}

void Assembler::jmpInstruction(std::string symbol)
{
    SymbolEntry *entry = this->symbolTable.findSymbol(symbol);

    // This symbol can be:
    // - undefined
    if (entry == nullptr)
    {
        SymbolEntry newEntry(0, -1, SymbolBind::UND, 0);
        this->symbolTable.addSymbol(newEntry, symbol);
        entry = this->symbolTable.findSymbol(symbol);
    }

    int32_t symbolSection = entry->section_id;
    uint32_t symbolVal = entry->value;

    // Symbol is in current section
    if (symbolSection == this->currentSection && entry->defined == true)
    {
        int32_t relativeOffset = symbolVal - ((this->locationCounter - 32) + 4); // relative to the next instruction

        // Check if the relative offset can fit within the signed 12-bit range (-2048 to 2047)
        if (relativeOffset >= -2048 && relativeOffset <= 2047)
        {
            MInstruction instr(OPCODE::JMP, 0, PC, 0, 0, relativeOffset);
            this->insertInstruction(instr);
            return;
        }
        else
        {
            // Error: relative offset out of range. Handle this case appropriately.
            std::cerr << "Error: Relative offset out of range for JMP in current section\n";
            return;
        }
    }

    // Symbol still not define or in another section, than just add jmp pc rel instruction in literal pool

    // Add literal to pool
    LiteralEntry newLiteral(0);

    uint32_t poolOffset = this->currSecPool.addLiteral(0);

    // Write instruction
    MInstruction instr(OPCODE::JMP, 8, PC, 0, 0, 0);
    this->insertInstruction(instr);

    // Add backpatch for poolOffset
    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
    this->poolZeroRela[poolOffset] = entry->index;
}

void Assembler::branch(int reg1, int reg2, uint32_t literal, uint8_t mode)
{
    // Same as jump just we use register for operands and different modes
    if (literal <= 0x0FFF)
    {
        MInstruction instr(OPCODE::JMP, mode, 0, reg1, reg2, literal);
        this->insertInstruction(instr);
        return;
    }

    // Add literal to pool
    LiteralEntry newLiteral(literal);

    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    // Write instruction
    mode += 8; // we make relative to pc jump now

    MInstruction instr(OPCODE::JMP, mode, PC, reg1, reg2, 0);
    this->insertInstruction(instr);

    // Add backpatch for poolOffset
    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
}

void Assembler::branch(int reg1, int reg2, std::string symbol, uint8_t mode)
{
    SymbolEntry *entry = this->symbolTable.findSymbol(symbol);

    // This symbol can be:
    // - undefined
    if (entry == nullptr)
    {
        SymbolEntry newEntry(0, -1, SymbolBind::UND, 0);
        this->symbolTable.addSymbol(newEntry, symbol);
        entry = this->symbolTable.findSymbol(symbol);
    }

    int32_t symbolSection = entry->section_id;
    uint32_t symbolVal = entry->value;

    // Symbol is in current section
    if (symbolSection == this->currentSection && entry->defined == true)
    {
        int32_t relativeOffset = symbolVal - ((this->locationCounter - 32) + 4); // relative to the next instruction

        // Check if the relative offset can fit within the signed 12-bit range (-2048 to 2047)
        if (relativeOffset >= -2048 && relativeOffset <= 2047)
        {
            MInstruction instr(OPCODE::JMP, mode, PC, reg1, reg2, relativeOffset);
            this->insertInstruction(instr);
            return;
        }
        else
        {
            // Error: relative offset out of range. Handle this case appropriately.
            std::cerr << "Error: Relative offset out of range for JMP in current section\n";
            return;
        }
    }

    // Symbol still not define and not in the same section, than just add jmp pc rel instruction in literal pool

    // Add literal to pool
    LiteralEntry newLiteral(0);

    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    // Write instruction
    mode += 8;

    MInstruction instr(OPCODE::JMP, mode, PC, reg1, reg2, 0);
    this->insertInstruction(instr);

    // Add backpatch for poolOffset
    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
    this->poolZeroRela[poolOffset] = entry->index;
}

void Assembler::callInstruction(uint32_t literal)
{
    if (literal <= 0x0FFF)
    {
        MInstruction instr(OPCODE::CALL, 0, 0, 0, 0, literal);
        this->insertInstruction(instr);
        return;
    }

    LiteralEntry newLiteral(literal);
    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    MInstruction instr(OPCODE::CALL, 1, PC, 0, 0, 0);
    this->insertInstruction(instr);

    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
}

void Assembler::callInstruction(std::string symbol)
{
    SymbolEntry *entry = this->symbolTable.findSymbol(symbol);

    if (entry == nullptr)
    {
        SymbolEntry newEntry(0, -1, SymbolBind::UND, 0);
        this->symbolTable.addSymbol(newEntry, symbol);
        entry = this->symbolTable.findSymbol(symbol);
    }

    int32_t symbolSection = entry->section_id;
    uint32_t symbolVal = entry->value;

    if (symbolSection == this->currentSection && entry->defined == true)
    {
        int32_t relativeOffset = symbolVal - (this->locationCounter + 4);

        if (relativeOffset >= -2048 && relativeOffset <= 2047)
        {
            MInstruction instr(OPCODE::CALL, 0, PC, 0, 0, relativeOffset);
            this->insertInstruction(instr);
            return;
        }
        else
        {
            // Error: relative offset out of range. Handle this case appropriately.
            std::cerr << "Error: Relative offset out of range for JMP in current section\n";
            return;
        }
    }

    LiteralEntry newLiteral(0);

    uint32_t poolOffset = this->currSecPool.addLiteral(0);

    MInstruction instr(OPCODE::CALL, 1, PC, 0, 0, 0);
    this->insertInstruction(instr);

    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
    this->poolZeroRela[poolOffset] = entry->index;
}

void Assembler::iretInstruction()
{
    MInstruction instr(OPCODE::LOAD, 6, STATUS, SP, 0, 4);
    this->insertInstruction(instr);

    MInstruction instr2(OPCODE::LOAD, 3, PC, SP, 0, 8);
    this->insertInstruction(instr2);
}