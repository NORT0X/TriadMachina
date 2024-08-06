#include "../common/Elf.hpp"
#include "../common/LiteralTable.hpp"
#include "../common/SymbolTable.hpp"
#include "../common/SectionTable.hpp"

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

    // Backpatching
    void addFlinkForSymbol(std::string symbolName, uint32_t position);
    void patchFlinksForSymbol(std::string symbolName);

    // Rembmer literal pool patches inside dips (which means all instructions must be pc relative)
    void poolPatching();

private:
    uint32_t locationCounter = 0;

    SectionIndex currentSection = 0;
    LiteralTable currSecPool;
    std::map<uint32_t, uint32_t> poolBackpatch; // address and offset inside pool to patch

    std::string outputFile;
    ElfFile eFile;

    SymbolTable symbolTable;
    SectionTable sectionTable;

    std::vector<ForwardRefEntry> forwardRefs;
};
