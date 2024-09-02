#include "../../inc/linker/Linker.hpp"

#include <iostream>

void Linker::addInputFile(std::string fileName)
{
    this->inputFiles.push_back(fileName);
}

void Linker::addPlace(std::string section, Address address)
{
    this->placeArguments[section] = address;
}

void Linker::run()
{
    // Parse all Object files
    for (std::string &file : inputFiles)
    {
        this->loadObjectFromFile(file);
    }

    if (isHex && isRelocatable)
    {
        std::cerr << "Can't use -hex and -relocatable at the same time.\n";
        return;
    }

    if (isHex)
    {
        this->makeHexFile();
        return;
    }

    if (isRelocatable)
    {
        this->makeRelocatableFile();
        return;
    }
}

void Linker::loadObjectFromFile(std::string fileName)
{

    Object obj(fileName);
    this->objects.emplace_back(std::move(obj));
}

void Linker::makeHexFile()
{
    // For each object
    for (Object &obj : this->objects)
    {
        for (SectionEntry &sec : obj.sectionTable.getTable())
        {

            std::string secName = obj.sectionTable.getName(sec.index);
            if (finishedSec.find(secName) != finishedSec.end())
            {
                continue;
            }

            finishedSec.insert(secName);

            auto it = placeArguments.find(secName);
            if (it != placeArguments.end())
            {
                currPosition = it->second;
            }

            this->writeSection(secName);
        }
    }

    if (this->symTable.checkAllDefined() == false)
    {
        throw std::runtime_error("Error: all symbols must be defined for -hex argument!\n");
    }

    // After finishing typing code and linekrs tables do relo
    this->fixRelocations();

    std::cout << "SymTable\n";
    std::cout << this->symTable << "\n\nSecTable\n";
    std::cout << this->secTable << "\n\nRelaTable\n";
    std::cout << this->relaTable.getSize() << '\n';
    std::cout << this->relaTable << '\n';

    this->writeBinaryHex();
}

void Linker::makeRelocatableFile()
{
    for (Object &obj : this->objects)
    {
        for (SectionEntry &sec : obj.sectionTable.getTable())
        {
            std::string secName = obj.sectionTable.getName(sec.index);
            if (finishedSec.find(secName) != finishedSec.end())
            {
                continue;
            }

            finishedSec.insert(secName);

            this->writeSection(secName);
        }
    }

    for (SectionEntry &sec : this->secTable.getTable())
    {
        sec.base += 32;
    }

    // Now write elf file
    this->writeRelocatableElf();
}

void Linker::writeSection(std::string section)
{
    std::size_t secSize = 0;

    SectionEntry entry(-1, this->currPosition, secSize);
    this->secTable.addSection(entry, section);

    uint32_t section_id = secTable.findSection(section)->index;

    for (Object &obj : this->objects)
    {
        for (SectionEntry &sec : obj.sectionTable.getTable())
        {
            if (obj.sectionTable.getName(sec.index) == section)
            {
                Address codePosition = sec.base - 32;

                for (int i = 0; i < sec.size; ++i)
                {
                    if (this->code.count(currPosition) > 0)
                    {
                        throw std::runtime_error("Linker: Section intersect.");
                    }

                    this->code[this->currPosition++] = obj.code[codePosition++];
                }

                // Add symbols in this section from object files
                for (SymbolEntry &sym : obj.symbolTable.getTable())
                {
                    if (sym.section_id == sec.index)
                    {
                        SymbolEntry *symFound = this->symTable.findSymbol(obj.symbolTable.getSymbolName(sym.index));
                        if (symFound == nullptr)
                        {
                            SymbolEntry symEntry(-1, section_id, SymbolBind::UND, 0);
                            this->symTable.addSymbol(symEntry, obj.symbolTable.getSymbolName(sym.index));
                            symFound = this->symTable.findSymbol(obj.symbolTable.getSymbolName(sym.index));
                        }

                        if (sym.defined == true && symFound->defined == true)
                        {
                            throw std::runtime_error("Error: multiple definition of " + obj.symbolTable.getSymbolName(sym.index) + "\n");
                        }

                        if (sym.defined == true)
                        {
                            uint32_t value = currPosition - sec.size + sym.value;
                            symFound->defined = true;
                            symFound->value = value;
                            symFound->section_id = section_id;
                            symFound->bind = SymbolBind::LOCAL_BIND;
                        }
                    }
                }

                // Adjust relocations in global rela table
                for (RelaEntry &rela : obj.relaTable.getTable())
                {
                    if (rela.section_id == sec.index)
                    {
                        std::string symbolName = obj.symbolTable.getSymbolName(rela.symbol_id);
                        SymbolEntry *globalSym = this->symTable.findSymbol(symbolName);
                        if (globalSym == nullptr)
                        {
                            SymbolEntry symEntry(-1, section_id, SymbolBind::UND, 0);
                            this->symTable.addSymbol(symEntry, symbolName);
                            globalSym = this->symTable.findSymbol(symbolName);
                        }

                        RelaEntry newRela(secSize + rela.offset, section_id, RelaType::ABS, globalSym->index, 0);
                        this->relaTable.addEntry(newRela);
                    }
                }

                secSize += sec.size;
            }
        }
    }

    this->secTable.findSection(section)->size = secSize;
}

void Linker::fixRelocations()
{
    for (RelaEntry &rela : this->relaTable.getTable())
    {
        std::string symbolName = this->symTable.getSymbolName(rela.symbol_id);
        SymbolEntry *symbolEntry = this->symTable.findSymbol(symbolName);

        SectionEntry *sectionEntry = this->secTable.findSection(rela.section_id);

        Address positionToFix = sectionEntry->base + rela.offset;

        if (this->code.count(positionToFix) == 0 ||
            this->code.count(positionToFix + 1) == 0 ||
            this->code.count(positionToFix + 2) == 0 ||
            this->code.count(positionToFix + 3) == 0)
        {
            throw std::runtime_error("Error: can't do relocation for position that is not used.\n");
        }

        this->code[positionToFix] = symbolEntry->value >> 8 * 3;
        this->code[positionToFix + 1] = symbolEntry->value >> 8 * 2;
        this->code[positionToFix + 2] = symbolEntry->value >> 8;
        this->code[positionToFix + 3] = symbolEntry->value;
    }
}

void Linker::writeBinaryHex()
{
    outFile.open(outFileName);

    for (const auto &pair : this->code)
    {
        std::vector<char> buff(5, 0);

        buff[0] = pair.first >> 8 * 3;
        buff[1] = pair.first >> 8 * 2;
        buff[2] = pair.first >> 8 * 1;
        buff[3] = pair.first;

        buff[4] = pair.second;

        std::cout << std::hex << std::uppercase                                // Set the output format to hexadecimal and uppercase
                  << std::setw(2) << std::setfill('0')                         // Ensure the hex output is always 2 characters long
                  << static_cast<int>(static_cast<unsigned char>(pair.second)) // Cast char to unsigned char, then to int
                  << " ";

        outFile.write(buff);
    }
    std::cout << std::dec;
}

void Linker::writeRelocatableElf()
{
    this->outFile.open(this->outFileName);

    std::vector<char> headerInitBuff(32, 0);
    this->outFile.write(headerInitBuff);

    std::vector<char> codeBuffer(this->code.size());

    for (const auto &[index, value] : this->code)
    {
        codeBuffer[index] = value;
    }

    this->outFile.write(codeBuffer);

    this->writeHeaderAndTables();
}

void Linker::writeHeaderAndTables()
{
    // Write code size
    this->outFile.writeAtPosition(0, 32);
    this->outFile.writeAtPosition(4, this->code.size());

    // Write symbol table info
    size_t tmp = this->outFile.getFileSize();
    this->outFile.writeAtPosition(8, tmp);
    this->outFile.write(this->symTable.getWriteData());
    this->outFile.writeAtPosition(12, this->outFile.getFileSize() - tmp);

    // Write section table info
    tmp = this->outFile.getFileSize();
    this->outFile.writeAtPosition(16, tmp);
    this->outFile.write(this->secTable.getWriteData());
    this->outFile.writeAtPosition(20, this->outFile.getFileSize() - tmp);

    // Write rela table info
    tmp = this->outFile.getFileSize();
    this->outFile.writeAtPosition(24, tmp);
    this->outFile.write(this->relaTable.getWriteData());
    this->outFile.writeAtPosition(28, this->outFile.getFileSize() - tmp);
}
