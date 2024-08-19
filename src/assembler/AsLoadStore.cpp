#include "../../inc/assembler/Assembler.hpp"
#include "../../inc/common/Elf.hpp"

#include <iostream>
#include <iomanip>

void Assembler::loadLiteral(uint32_t literal, int reg, LiteralMode mode)
{
    switch (mode)
    {
    case LiteralMode::VALUE:
    {
        // We just have to load literal value directly into reg

        // If value is less than 0x0fff we don't need pool
        if (literal <= 0x0FFF)
        {
            MInstruction instr(OPCODE::LOAD, 1, reg, 0, 0, literal);
            this->insertInstruction(instr);
            break;
        }

        // If not put mem ind in literal pool
        LiteralEntry newLiteral(literal);
        std::cout << literal << '\n';
        uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

        MInstruction instr(OPCODE::LOAD, 2, reg, PC, 0, 0);
        this->insertInstruction(instr);

        // Add backpatch for poolOffset
        uint32_t place = this->locationCounter - 4;
        this->poolBackpatch[place] = poolOffset;

        break;
    }
    case LiteralMode::MEMORY:
    {
        // This is when literal points to memory where value we want to lode is

        if (literal <= 0x0FFF)
        {
            MInstruction instr(OPCODE::LOAD, 2, reg, 0, 0, literal);
            this->insertInstruction(instr);
            break;
        }

        // If literal larger than 0x0FFF than we have to use literal pool
        // Here is the catch: we have to write two instructions for this
        // First one we catch value from literal pool
        // Secon we use memory from that register to get value
        LiteralEntry newLiteral(literal);
        uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

        MInstruction instr(OPCODE::LOAD, 2, reg, PC, 0, 0);
        this->insertInstruction(instr);

        // Add backpatch for poolOffset
        uint32_t place = this->locationCounter - 4;
        this->poolBackpatch[place] = poolOffset;

        // Now do reg <= [reg] --- [reg] will be [literal_value]

        MInstruction instr2(OPCODE::LOAD, 2, reg, reg, 0, 0);
        this->insertInstruction(instr2);
        break;
    }
    }
}

void Assembler::loadReg(int operandReg, int dstReg, RegMode mode)
{
    switch (mode)
    {
    case RegMode::REG_DIR:
    {
        MInstruction instr(OPCODE::LOAD, 1, dstReg, operandReg, 0, 0);
        this->insertInstruction(instr);
        break;
    }
    case RegMode::REG_IND:
    {
        MInstruction instr(OPCODE::LOAD, 2, dstReg, operandReg, 0, 0);
        this->insertInstruction(instr);
        break;
    }
    }
}

void Assembler::loadRegLiteral(int operandReg, uint32_t literal, int dstReg)
{
    // Check if we need literal pool
    if (literal <= 0x0FFF)
    {
        MInstruction instr(OPCODE::LOAD, 2, dstReg, operandReg, 0, literal);
        this->insertInstruction(instr);
        return;
    }

    // If we need literal pool we have to code this with 2 instructions
    // First get value from pool to register than load

    // add Literal to pool
    LiteralEntry newLiteral(literal);
    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    MInstruction instr(OPCODE::LOAD, 2, dstReg, PC, 0, 0);
    this->insertInstruction(instr);

    // Add backpatch for poolOffset
    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;

    // Now do reg <= [reg + reg]

    MInstruction instr2(OPCODE::LOAD, 2, dstReg, dstReg, operandReg, 0);
    this->insertInstruction(instr2);
}

void Assembler::loadSymbol(std::string symbol, int dstReg, SymbolMode mode)
{
    // Here we put symbol just in rela table because we don't know label value

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

        MInstruction instr(OPCODE::LOAD, 2, dstReg, PC, 0, 0);
        this->insertInstruction(instr);

        // Add backpatch for poolOffset and rela
        uint32_t place = this->locationCounter - 4;
        this->poolBackpatch[place] = poolOffset;
        this->poolZeroRela[poolOffset] = entry->index;

        break;
    }
    case SymbolMode::MEMORY:
    {
        // Same as VALUE but we need to code two instructions
        // One to get value of symbol into reg
        // And other one is reg <= [reg]

        LiteralEntry newLiteral(0);
        uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

        MInstruction instr(OPCODE::LOAD, 2, dstReg, PC, 0, 0);
        this->insertInstruction(instr);

        // Add backpatch of poolOffset and rela
        uint32_t place = this->locationCounter - 4;
        this->poolBackpatch[place] = poolOffset;
        this->poolZeroRela[poolOffset] = entry->index;

        // Now do reg <= [reg] --- [reg] will be [symbol_value]
        MInstruction instr2(OPCODE::LOAD, 2, dstReg, dstReg, 0, 0);
        this->insertInstruction(instr2);
    }
    }
}

void Assembler::storeLiteral(int reg, uint32_t literal_dst)
{
    // Literal src is memory where we want to store value from register

    if (literal_dst <= 0x0FFF)
    {
        MInstruction instr(OPCODE::STORE, 0, 0, 0, reg, literal_dst);
        this->insertInstruction(instr);
        return;
    }

    // In this case we need literal pool
    // store literal in pool and do mem[mem[pc + offset]] <= reg

    LiteralEntry newLiteral(literal_dst);
    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    MInstruction instr(OPCODE::STORE, 2, PC, 0, reg, 0);
    this->insertInstruction(instr);

    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
}

void Assembler::storeReg(int reg_src, int reg_dst)
{
    // [reg_dst] <= reg_src

    MInstruction instr(OPCODE::STORE, 0, reg_dst, 0, reg_src, 0);
    this->insertInstruction(instr);
}

void Assembler::storeRegLiteral(int reg_src, int reg_dst, uint32_t literal_dst)
{
    if (literal_dst < 0x0FFF)
    {
        MInstruction instr(OPCODE::STORE, 0, reg_dst, 0, reg_src, literal_dst);
        this->insertInstruction(instr);
        return;
    }

    LiteralEntry newLiteral(literal_dst);
    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    MInstruction instr(OPCODE::STORE, 2, PC, reg_dst, reg_src, 0);

    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
}

void Assembler::storeSymbol(int reg_src, std::string symbol_dst)
{
    // Check if symbol is already in symbol table
    SymbolEntry *entry = this->symbolTable.findSymbol(symbol_dst);

    if (entry == nullptr)
    {
        SymbolEntry newSymbol(0, -1, SymbolBind::UND, 0);
        this->symbolTable.addSymbol(newSymbol, symbol_dst);
        entry = this->symbolTable.findSymbol(symbol_dst);
    }

    // Add 0 to literal pool so later value of symbol can be put (in linking part)
    LiteralEntry newLiteral(0);
    uint32_t poolOffset = this->currSecPool.addLiteral(newLiteral);

    // Write instruction
    MInstruction instr(OPCODE::STORE, 2, PC, 0, reg_src, 0);
    this->insertInstruction(instr);

    uint32_t place = this->locationCounter - 4;
    this->poolBackpatch[place] = poolOffset;
    this->poolZeroRela[poolOffset] = entry->index;
}