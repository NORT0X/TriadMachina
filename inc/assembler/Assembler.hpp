#include "../common/Elf.hpp"
#include "../common/LiteralTable.hpp"
#include "../common/SymbolTable.hpp"
#include "../common/SectionTable.hpp"
#include "../common/RelaTable.hpp"

#include <cstdint>
#include <string>
#include <map>

class Assembler
{
public:
    Assembler(std::string outputFile);

    void end();
    void skipDirective(uint32_t literal);
    void globalDirective(std::string name);
    void externDirective(std::string name);
    void sectionDirective(std::string sectionName);
    void wordDirectiveLiteral(uint32_t literal);
    void wordDirectiveSymbol(std::string symbolName);

    void label(std::string labelName);

    void addInstruction(int regA, int regB);
    void subInstruction(int regA, int regB);
    void mulInstruction(int regA, int regB);
    void divInstruction(int regA, int regB);

    void notInstruction(int regA);
    void andInstruction(int regA, int regB);
    void orInstruction(int regA, int regB);
    void xorInstruction(int regA, int regB);
    void shlInstruction(int regA, int regB);
    void shrInstruction(int regA, int regB);

    void popInstruction(int regA);
    void pushInstruction(int regB);

    void haltInstruction();

    void jmpInstruction(uint32_t literal);
    void jmpInstruction(std::string symbol);
    void branch(int reg1, int reg2, uint32_t literal, uint8_t mode);
    void branch(int reg1, int reg2, std::string symbol, uint8_t mode);

    void loadLiteral(uint32_t literal, int reg, LiteralMode mode);
    void loadReg(int operandReg, int dstReg, RegMode mode);
    void loadRegLiteral(int operandReg, uint32_t literal, int dstReg);
    void loadSymbol(std::string symbol, int dstReg, SymbolMode mode);

    void storeLiteral(int reg, uint32_t literal_dst);
    void storeReg(int reg_src, int reg_dst);
    void storeRegLiteral(int reg_src, int reg_dst, uint32_t literal_dst);
    void storeSymbol(int reg_src, std::string symbol);

    void intInstruction();
    void callInstruction(uint32_t literal);
    void callInstruction(std::string symbol);

    // Backpatching
    void addFlinkForSymbol(std::string symbolName, uint32_t position);
    void patchFlinksForSymbol(std::string symbolName);

    void addAbsRela(std::string symbol);

    // Rembmer literal pool patches inside dips (which means all instructions must be pc relative)
    void poolPatching();

private:
    uint32_t locationCounter = 0;

    SectionIndex currentSection = 0;
    LiteralTable currSecPool;
    std::map<uint32_t, uint32_t> poolBackpatch; // address and offset inside pool to patch
    std::map<uint32_t, SymbolIndex> poolZeroRela;

    std::string outputFile;
    ElfFile eFile;

    SymbolTable symbolTable;
    SectionTable sectionTable;

    RelaTable relaTable;

    std::vector<ForwardRefEntry> forwardRefs;
};
