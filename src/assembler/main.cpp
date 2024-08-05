#include "../../inc/assembler/Assembler.hpp"

#include <cstdio>
#include <iostream>

#include <stdio.h>
#include <string>
#include <memory>

using namespace std;
extern int yylex(void);
extern int yyparse();
extern FILE *yyin;

unique_ptr<Assembler> as;

int main()
{
    std::string fileName = "test.as";
    FILE *myFile = fopen(fileName.c_str(), "r");

    if (!myFile)
    {
        std::cout << "Couldn't open file " << fileName << std::endl;
        return -1;
    }

    std::string outFile = "test.o";
    as = make_unique<Assembler>(outFile);

    yyin = myFile;

    yyparse();

    std::cout << "Praser done!" << std::endl;
}
