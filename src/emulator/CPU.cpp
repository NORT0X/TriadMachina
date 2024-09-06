#include "../../inc/emulator/CPU.hpp"
#include "../../inc/emulator/Memory.hpp"

#include <iostream>
#include <iomanip>

CPU::CPU()
{
    reset();
}

void CPU::reset()
{
    GPR[PC] = 0x40000000;
    GPR[SP] = 0xFFFFFF00;
    GPR[0] = 0;
    for (int i = 1; i < 14; ++i)
    {
        GPR[i] = 0;
    }

    running = false;
}

void CPU::tick()
{
    fetch();
    execute();
    GPR[0] = 0;
}

void CPU::fetch()
{
    for (int i = 3; i >= 0; --i)
    {
        IR[i] = memory->read(GPR[PC]++);
    }

    currentInstruction.OC = static_cast<OPCODE>((IR[0] >> 4) & 0x0F);
    currentInstruction.MOD = IR[0] & 0x0F;
    currentInstruction.A = (IR[1] >> 4) & 0x0F;
    currentInstruction.B = IR[1] & 0x0F;
    currentInstruction.C = (IR[2] >> 4) & 0x0F;
    currentInstruction.DISP = ((IR[2] & 0x0F) << 8) | (0xFF & IR[3]);
    if ((currentInstruction.DISP & (1 << 11)) != 0)
    {
        currentInstruction.DISP |= 0xFFFFF000;
    }
}

void CPU::execute()
{
    switch (currentInstruction.OC)
    {
    case OPCODE::HALT:
    {
        running = false;
        break;
    }
    case OPCODE::INT:
    {
        push(CSR[STATUS]);
        push(GPR[PC]);
        CSR[CAUSE] = 4;
        CSR[STATUS] = CSR[STATUS] & (~0x1);
        GPR[PC] = CSR[HANDLER];
        break;
    }
    case OPCODE::CALL:
    {
        callInstr();
        break;
    }
    case OPCODE::JMP:
    {
        jmpInstr();
        break;
    }
    case OPCODE::XCHG:
    {
        uint32_t tmp = GPR[currentInstruction.B];
        GPR[currentInstruction.B] = GPR[currentInstruction.C];
        GPR[currentInstruction.C] = tmp;
        break;
    }
    case OPCODE::ARITHMETIC:
    {
        arithmeticInstr();
        break;
    }
    case OPCODE::LOGIC:
    {
        logicInstr();
        break;
    }
    case OPCODE::SHIFT:
    {
        switch (currentInstruction.MOD)
        {
        case 0x0:
        {
            GPR[currentInstruction.A] = GPR[currentInstruction.B] << GPR[currentInstruction.C];
            break;
        }
        case 0x1:
        {
            GPR[currentInstruction.A] = GPR[currentInstruction.B] >> GPR[currentInstruction.C];
            break;
        }
        default:
        {
            throw std::runtime_error("Error: wrong mode for SHIFT instruction at address: " + GPR[PC]);
        }
        }
        break;
    }
    case OPCODE::LOAD:
    {
        loadInstr();
        break;
    }
    case OPCODE::STORE:
    {
        storeInstr();
        break;
    }
    default:
    {
        throw std::runtime_error("Error: wrong opcode at address: " + GPR[PC - 4]);
    }
    }
}

void CPU::badInstrInt()
{
    push(CSR[STATUS]);
    push(CSR[PC]);
    CSR[CAUSE] = INT_CAUSE::BAD_INSTR;
    CSR[STATUS] = CSR[STATUS] & (~0x4);
    GPR[PC] = CSR[HANDLER];
}

void CPU::push(uint32_t reg)
{
    GPR[SP] -= 4;
    memory->write32(GPR[SP], reg);
}

uint32_t CPU::pop()
{
    uint32_t res = memory->read32(GPR[SP]);
    GPR[SP] += 4;

    return res;
}

void CPU::callInstr()
{
    switch (currentInstruction.MOD)
    {
    case 0x0:
    {
        push(GPR[PC]);
        GPR[PC] = GPR[currentInstruction.A] + GPR[currentInstruction.B] + currentInstruction.DISP;
        break;
    }
    case 0x1:
    {
        push(GPR[PC]);
        Address addr = GPR[currentInstruction.A] + GPR[currentInstruction.B] + currentInstruction.DISP;
        GPR[PC] = this->memory->read32(addr);
        break;
    }
    default:
    {
        badInstrInt();
    }
    }
}

void CPU::jmpInstr()
{
    switch (currentInstruction.MOD)
    {
    case 0x0:
    {
        GPR[PC] = GPR[currentInstruction.A] + currentInstruction.DISP;
        break;
    }
    case 0x1:
    {
        if (GPR[currentInstruction.B] == GPR[currentInstruction.C])
        {
            GPR[PC] = GPR[currentInstruction.A] + currentInstruction.DISP;
        }
        break;
    }
    case 0x2:
    {
        if (GPR[currentInstruction.B] != GPR[currentInstruction.C])
        {
            GPR[PC] = GPR[currentInstruction.A] + currentInstruction.DISP;
        }
        break;
    }
    case 0x3:
    {
        if (GPR[currentInstruction.B] > GPR[currentInstruction.C])
        {
            GPR[PC] = GPR[currentInstruction.A] + currentInstruction.DISP;
        }
        break;
    }
    case 0x8:
    {
        Address addr = GPR[currentInstruction.A] + currentInstruction.DISP;
        GPR[PC] = memory->read32(addr);
        break;
    }
    case 0x9:
    {
        if (GPR[currentInstruction.B] == GPR[currentInstruction.C])
        {
            Address addr = GPR[currentInstruction.A] + currentInstruction.DISP;
            GPR[PC] = memory->read32(addr);
        }
        break;
    }
    case 0xA:
    {
        if (GPR[currentInstruction.B] != GPR[currentInstruction.C])
        {
            Address addr = GPR[currentInstruction.A] + currentInstruction.DISP;
            GPR[PC] = memory->read32(addr);
        }
        break;
    }
    case 0xB:
    {
        if (GPR[currentInstruction.B] > GPR[currentInstruction.C])
        {
            Address addr = GPR[currentInstruction.A] + currentInstruction.DISP;
            GPR[PC] = memory->read32(addr);
        }
        break;
    }
    default:
    {
        badInstrInt();
    }
    }
}

void CPU::arithmeticInstr()
{
    switch (currentInstruction.MOD)
    {
    case 0x0:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.B] + GPR[currentInstruction.C];
        break;
    }
    case 0x1:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.B] - GPR[currentInstruction.C];
        break;
    }
    case 0x2:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.B] * GPR[currentInstruction.C];
        break;
    }
    case 0x3:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.B] / GPR[currentInstruction.C];
        break;
    }
    default:
    {
        badInstrInt();
    }
    }
}

void CPU::logicInstr()
{
    switch (currentInstruction.MOD)
    {
    case 0x0:
    {
        GPR[currentInstruction.A] = ~GPR[currentInstruction.B];
        break;
    }
    case 0x1:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.B] & GPR[currentInstruction.C];
        break;
    }
    case 0x2:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.B] | GPR[currentInstruction.C];
        break;
    }
    case 0x3:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.B] ^ GPR[currentInstruction.C];
        break;
    }
    default:
    {
        badInstrInt();
    }
    }
}

void CPU::loadInstr()
{
    switch (currentInstruction.MOD)
    {
    case 0x0:
    {
        GPR[currentInstruction.A] = CSR[currentInstruction.B];
        break;
    }
    case 0x1:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.B] + currentInstruction.DISP;
        break;
    }
    case 0x2:
    {
        Address addr = GPR[currentInstruction.B] + GPR[currentInstruction.C] + currentInstruction.DISP;
        GPR[currentInstruction.A] = memory->read32(addr);
        break;
    }
    case 0x3:
    {
        Address addr = GPR[currentInstruction.B];
        GPR[currentInstruction.A] = memory->read32(addr);
        GPR[currentInstruction.B] = GPR[currentInstruction.B] + currentInstruction.DISP;
        break;
    }
    case 0x4:
    {
        CSR[currentInstruction.A] = GPR[currentInstruction.B];
        break;
    }
    case 0x5:
    {
        CSR[currentInstruction.A] = CSR[currentInstruction.B] | currentInstruction.DISP;
        break;
    }
    case 0x6:
    {
        Address addr = GPR[currentInstruction.B] + GPR[currentInstruction.C] + currentInstruction.DISP;
        CSR[currentInstruction.A] = memory->read32(addr);
        break;
    }
    case 0x7:
    {
        Address addr = GPR[currentInstruction.B];
        CSR[currentInstruction.A] = memory->read32(addr);
        GPR[currentInstruction.B] = GPR[currentInstruction.B] + currentInstruction.DISP;
        break;
    }
    }
}

void CPU::storeInstr()
{
    switch (currentInstruction.MOD)
    {
    case 0x0:
    {
        Address addr = GPR[currentInstruction.A] + GPR[currentInstruction.B] + currentInstruction.DISP;
        memory->write32(addr, GPR[currentInstruction.C]);
        break;
    }
    case 0x2:
    {
        Address addr = GPR[currentInstruction.A] + GPR[currentInstruction.B] + currentInstruction.DISP;
        addr = memory->read32(addr);
        memory->write32(addr, GPR[currentInstruction.C]);
        break;
    }
    case 0x1:
    {
        GPR[currentInstruction.A] = GPR[currentInstruction.A] + currentInstruction.DISP;
        Address addr = GPR[currentInstruction.A];
        memory->write32(addr, GPR[currentInstruction.C]);
        break;
    }
    default:
    {
        badInstrInt();
    }
    }
}

std::ostream &operator<<(std::ostream &os, const CPU &cpu)
{
    os << "-----------------------------------------------------------------" << std::endl;
    os << "Emulated processor executed halt instruction" << std::endl;
    os << "Emulated processor state:" << std::endl;

    // Iterate through the general-purpose registers and print them
    for (int i = 0; i < 16; ++i)
    {
        // Print each register in hexadecimal format
        os << "r" << i << "=0x"
           << std::setw(8) << std::setfill('0') << std::hex << std::uppercase
           << cpu.GPR[i] << " ";

        // Print a newline after every 4 registers to match the desired format
        if ((i + 1) % 4 == 0)
        {
            os << std::endl;
        }
    }

    return os;
}