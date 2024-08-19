#include "../../inc/linker/Object.hpp"

#include <iostream>

Object::Object(std::string fileName)
{
    this->eFile.openForRead(fileName);

    this->loadObjectFile();

    this->eFile.close();
}

void Object::loadObjectFile()
{
    this->loadHeader();

    // Read code
    this->eFile.readAtPosition(this->header.codeStart, this->code, this->header.codeSize);

    std::vector<char> buff;

    // Read SymbolTable
    this->eFile.readAtPosition(this->header.symStart, buff, this->header.symSize);
    this->symbolTable.readFromData(buff);
    buff.clear();

    // Read SectionTable
    this->eFile.readAtPosition(this->header.secStart, buff, this->header.secSize);
    this->sectionTable.readFromData(buff);
    buff.clear();

    // Read RelaTable
    this->eFile.readAtPosition(this->header.relaStart, buff, this->header.relaSize);
    this->relaTable.readFromData(buff);
    buff.clear();
}

void Object::loadHeader()
{
    this->eFile.readAtPosition(0, this->header.codeStart);
    this->eFile.readAtPosition(4, this->header.codeSize);

    this->eFile.readAtPosition(8, this->header.symStart);
    this->eFile.readAtPosition(12, this->header.symSize);

    this->eFile.readAtPosition(16, this->header.secStart);
    this->eFile.readAtPosition(20, this->header.secSize);

    this->eFile.readAtPosition(24, this->header.relaStart);
    this->eFile.readAtPosition(28, this->header.relaSize);
}
