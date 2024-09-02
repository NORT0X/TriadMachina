#include "../../inc/emulator/CPU.hpp"
#include "../../inc/emulator/Memory.hpp"

CPU::CPU()
{
    this->reset();
}

void CPU::reset()
{
    this->GPR[PC] = 0x40000000;
    this->GPR[SP] = 0xFFFFFF00;
    this->GPR[0] = 0;

    for (int i = 1; i < 14; ++i)
    {
        this->GPR[i] = 0;
    }
}

void CPU::fetch()
{
    for (int i = 3; i >= 0; --i)
    {
        IR[i] = this->memory->read(this->GPR[PC]++);
    }

    this->currentInstruction.OC = static_cast<OPCODE>((IR[0] >> 4) & 0x0F);
    this->currentInstruction.MOD = IR[0] & 0x0F;
    this->currentInstruction.A = (IR[1] >> 4) & 0x0F;
    this->currentInstruction.B = IR[1] & 0x0F;
    this->currentInstruction.C = (IR[2] >> 4) & 0x0F;
}
