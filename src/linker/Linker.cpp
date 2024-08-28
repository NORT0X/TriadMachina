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
    ElfFile eFile;

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

            this->writeSection(secName, OutType::HEX);
        }
    }

    // After finishing typing code and linekrs tables do relo
    std::cout << "SymTable\n";
    std::cout << this->symTable << "\n\nSecTable\n";
    std::cout << this->secTable << "\n\nRelaTable\n";
    std::cout << this->relaTable.getSize() << '\n';
    std::cout << this->relaTable << '\n';
}

void Linker::makeRelocatableFile()
{
}

void Linker::writeSection(std::string section, OutType type = OutType::HEX)
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