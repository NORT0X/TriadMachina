#include "../../inc/assembler/Assembler.hpp"
#include "../../inc/common/Elf.hpp"

#include <iostream>
#include <bitset>

Assembler::Assembler(std::string outputFile) : outputFile(outputFile)
{
    this->eFile.open(outputFile);
    this->symbolTable = SymbolTable();
    this->sectionTable = SectionTable();
}

void Assembler::end()
{
    // Update last section size and write pool
    if (this->sectionTable.tableSize() > 0)
    {
        SectionEntry *lastSection = this->sectionTable.findSection(this->sectionTable.tableSize() - 1);
        lastSection->size = this->locationCounter - lastSection->base;

        // Write pool
        this->eFile.write(this->currSecPool.getWriteData());
        // Size of pool to locationCounter
        this->locationCounter += this->currSecPool.getSizeInBytes();

        // Do pool backpatching
        this->poolPatching();
        this->poolBackpatch.clear(); // Delete map boolBackpatching

        this->currSecPool.clear();
    }

    // Print
    std::cout << "\n\nSymbolTable\n\n";
    std::cout << this->symbolTable;
    std::cout << "\n\nSectionTable\n\n";
    std::cout << this->sectionTable;
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
    if (this->sectionTable.tableSize() > 0)
    {
        SectionEntry *prevSection = this->sectionTable.findSection(currentSection);
        prevSection->size = this->locationCounter - prevSection->base;

        // Write current literal pool at the end of section and clear it for next
        this->eFile.write(this->currSecPool.getWriteData());
        // Add size of pool to locationCounter
        this->locationCounter += this->currSecPool.getSizeInBytes();

        // Do pool backpatching
        this->poolPatching();
        this->poolBackpatch.clear(); // Delete map boolBackpatching

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

    // if symbol is found just do the same with its value as with literal
    if (entry != nullptr && entry->defined == true)
    {
        buff[0] = entry->value >> 8 * 3;
        buff[1] = entry->value >> 8 * 2;
        buff[2] = entry->value >> 8;
        buff[3] = entry->value;
    }
    else
    {
        // All zeros will be placed instead while we dont get to definition of symbol
        this->addFlinkForSymbol(symbolName, locationCounter);
    }

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
        exists->value = this->locationCounter;
        exists->section_id = this->currentSection;
        exists->defined = true;
    }

    // If it's not already in symbol table that means that it's local variable
    if (exists == nullptr)
    {
        SymbolEntry entry(0, this->currentSection, SymbolBind::LOCAL_BIND, this->locationCounter, true);
        this->symbolTable.addSymbol(entry, labelName);
        std::cout << this->symbolTable.findSymbol(labelName)->defined;
    }

    // Backpatching
    this->patchFlinksForSymbol(labelName);
}

void Assembler::addInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01010000;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::subInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01010001;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::mulInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01010010;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::divInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01010011;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::notInstruction(int regA)
{
    std::cout << "Test " << regA << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01100000;
    buff[1] = ((regA & 0x0F) << 4) | (regA & 0x0F);

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::andInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01100001;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::orInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01100010;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::xorInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01100011;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::shlInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01110000;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::shrInstruction(int regA, int regB)
{
    std::cout << "Test " << regA << regB << '\n';
    std::vector<char> buff(4, 0);
    buff[0] = 0b01110001;
    buff[1] = ((regB & 0x0F) << 4) | (regB & 0x0F);
    buff[2] = ((regA & 0x0F) << 4) | 0x00;

    for (char c : buff)
    {
        std::cout << std::bitset<8>(c) << ' ';
    }
    std::cout << std::endl;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::popInstruction(int regA)
{
}

void Assembler::pushInstruction(int regB)
{
}

void Assembler::haltInstruction()
{
    std::vector<char> buff(4, 0);

    this->eFile.write(buff);
}

void Assembler::jmpInstruction(uint32_t literal)
{
    std::vector<char> buff(4, 0);
    if (literal < 0x00000fff)
    {
        buff[0] = 0b00110000;
        buff[1] = 0;
        buff[2] = (literal >> 8) & 0x0F;
        buff[3] = literal;

        this->eFile.write(buff);
        this->locationCounter += 4;
        return;
    }
    // In other case we have to put in literal pool for current section and that's it
    // And do pc <= mem32[pc + disp(sec_base + literal_pool + offset)]
    // Displacement should linker fix later

    // Add literal to pool
    LiteralEntry newLiteral(literal);

    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    // Write instruction
    buff[0] = 0b00111000;
    buff[1] = 0xF0;
    buff[2] = 0;
    buff[3] = 0;

    this->eFile.write(buff);
    this->locationCounter += 4;

    // Add backpatch for poolOffset
    uint32_t place = this->locationCounter - 2;
    this->poolBackpatch[place] = poolOffset;
}

void Assembler::jmpInstruction(std::string symbol)
{
    // test
}