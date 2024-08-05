#include "../common/Elf.hpp"
#include "../common/SymbolTable.hpp"

#include <cstdint>
#include <string>

class Assembler
{
public:
    Assembler(std::string outputFile);

    void end();
    void skipDirective(uint32_t literal);
    void globalDirective(std::string name);
    void externDirective(std::string name);
    void sectionDirective(std::string sectionName);

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

private:
    uint32_t locationCounter = 0;
    SectionIndex currentSection = 0;

    std::string outputFile;
    ElfFile eFile;

    SymbolTable symbolTable;
};
