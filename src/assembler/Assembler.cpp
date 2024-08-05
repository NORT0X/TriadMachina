#include "../../inc/assembler/Assembler.hpp"
#include "../../inc/common/Elf.hpp"

#include <iostream>
#include <bitset>

Assembler::Assembler(std::string outputFile) : outputFile(outputFile)
{
    this->eFile.open(outputFile);
    this->symbolTable = SymbolTable();
}

void Assembler::end()
{
    std::cout << this->symbolTable;
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