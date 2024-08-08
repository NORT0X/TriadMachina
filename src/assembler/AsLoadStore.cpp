#include "../../inc/assembler/Assembler.hpp"
#include "../../inc/common/Elf.hpp"

#include <iostream>
#include <iomanip>

void Assembler::loadLiteral(uint32_t literal, int reg, LiteralMode mode)
{
    std::vector<char> buff(4, 0);

    switch (mode)
    {
    case LiteralMode::VALUE:
    {
        // We just have to load literal value directly into reg

        // If value is less than 0x0fff we don't need pool
        if (literal <= 0x0FFF)
        {
            buff[0] = 0x91;
            buff[1] = static_cast<uint8_t>(reg << 4);
            buff[2] = 0x0F & (literal >> 8);
            buff[3] = literal;
            this->eFile.write(buff);
            break;
        }

        // If not put mem ind in literal pool
        LiteralEntry newLiteral(literal);
        uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

        buff[0] = 0x92;
        buff[1] = 0x0F | static_cast<uint8_t>(reg << 4);
        buff[2] = 0;
        buff[3] = 0;

        this->eFile.write(buff);

        // Add backpatch for poolOffset
        uint32_t place = this->locationCounter + 2;
        this->poolBackpatch[place] = poolOffset;
    }
    case LiteralMode::MEMORY:
    {
        // This is when literal points to memory where value we want to lode is

        if (literal <= 0x0FFF)
        {
            buff[0] = 0x92;
            buff[1] = static_cast<uint8_t>(reg << 4);
            buff[2] = 0x0F & (literal >> 8);
            buff[3] = literal;
            this->eFile.write(buff);
            break;
        }

        // If literal larger than 0x0FFF than we have to use literal pool
        // Here is the catch: we have to write two instructions for this
        // First one we catch value from literal pool
        // Secon we use memory from that register to get value
        LiteralEntry newLiteral(literal);
        uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

        buff[0] = 0x92;
        buff[1] = 0x0F | static_cast<uint8_t>(reg << 4);
        buff[2] = 0;
        buff[3] = 0;

        this->eFile.write(buff);
        this->locationCounter += 4; // since there will be one more instruction

        // Add backpatch for poolOffset
        uint32_t place = this->locationCounter - 2;
        this->poolBackpatch[place] = poolOffset;

        // Now do reg <= [reg] --- [reg] will be [literal_value]

        buff[0] = 0x92;
        buff[1] = static_cast<uint8_t>(reg << 4) | (reg & 0x0F);
        buff[2] = 0;
        buff[3] = 0;
        this->eFile.write(buff);
    }
    }

    this->locationCounter += 4;
}

void Assembler::loadReg(int operandReg, int dstReg, RegMode mode)
{
    std::vector<char> buff(4, 0);

    switch (mode)
    {
    case RegMode::REG_DIR:
    {

        buff[0] = 0x91;
        buff[2] = static_cast<uint8_t>(dstReg << 4) | (operandReg & 0x0F);
        this->eFile.write(buff);
    }
    case RegMode::REG_IND:
    {
        buff[0] = 0x92;
        buff[2] = static_cast<uint8_t>(dstReg << 4) | (operandReg & 0x0F);
        this->eFile.write(buff);
    }
    }
    this->locationCounter += 4;
}

void Assembler::loadRegLiteral(int operandReg, uint32_t literal, int dstReg)
{
    std::vector<char> buff(4, 0);

    // Check if we need literal pool
    if (literal <= 0x0FFF)
    {
        buff[0] = 0x92;
        buff[1] = static_cast<uint8_t>(dstReg << 4) | (operandReg & 0x0F);
        buff[2] = 0x0F & (literal >> 8);
        buff[3] = literal;
        this->eFile.write(buff);

        this->locationCounter += 4;
        return;
    }

    // If we need literal pool we have to code this with 2 instructions
    // First get value from pool to register than load

    // add Literal to pool
    LiteralEntry newLiteral(literal);
    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    buff[0] = 0x92;
    buff[1] = 0x0F | static_cast<uint8_t>(dstReg << 4);
    buff[2] = 0;
    buff[3] = 0;

    this->eFile.write(buff);
    this->locationCounter += 4; // since there will be one more instruction

    // Add backpatch for poolOffset
    uint32_t place = this->locationCounter - 2;
    this->poolBackpatch[place] = poolOffset;

    // Now do reg <= [reg + reg]

    buff[0] = 0x92;
    buff[1] = (dstReg << 4) | dstReg;
    buff[2] = operandReg << 4;
    buff[3] = 0;

    this->eFile.write(buff);
    this->locationCounter += 4;
}

void Assembler::loadSymbol(std::string symbol, int dstReg, SymbolMode mode)
{
    // Here we put symbol just in rela table because we don't know label value
    std::vector<char> buff(4, 0);

    // Check if symbol is already in symbol table
    SymbolEntry *entry = this->symbolTable.findSymbol(symbol);

    if (entry == nullptr)
    {
        SymbolEntry newSymbol(0, -1, SymbolBind::UND, 0);
        this->symbolTable.addSymbol(newSymbol, symbol);
        entry = this->symbolTable.findSymbol(symbol);
    }

    switch (mode)
    {
    case SymbolMode::VALUE:
    {
        // Add 0 to literal pool so later value of symbol can be put (in linking part)
        LiteralEntry newLiteral(0);
        uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

        // Write instruction

        buff[0] = 0x92;
        buff[1] = (dstReg << 4) | 0x0F;
        buff[2] = 0;
        buff[3] = 0;

        this->eFile.write(buff);
        this->locationCounter += 4;

        // Add backpatch for poolOffset and rela
        uint32_t place = this->locationCounter - 2;
        this->poolBackpatch[place] = poolOffset;
        this->poolZeroRela[poolOffset] = entry->index;
    }
    case SymbolMode::MEMORY:
    {
        // Same as VALUE but we need to code two instructions
        // One to get value of symbol into reg
        // And other one is reg <= [reg]

        LiteralEntry newLiteral(0);
        uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

        buff[0] = 0x92;
        buff[1] = 0x0F | static_cast<uint8_t>(dstReg << 4);
        buff[2] = 0;
        buff[3] = 0;

        this->eFile.write(buff);
        this->locationCounter += 4;

        // Add backpatch of poolOffset and rela
        uint32_t place = this->locationCounter - 2;
        this->poolBackpatch[place] = poolOffset;
        this->poolZeroRela[poolOffset] = entry->index;

        // Now do reg <= [reg] --- [reg] will be [symbol_value]
        buff[0] = 0x92;
        buff[1] = static_cast<uint8_t>(dstReg << 4) | (dstReg & 0x0F);
        buff[2] = 0;
        buff[3] = 0;
        this->eFile.write(buff);
        this->locationCounter += 4;
    }
    }
}