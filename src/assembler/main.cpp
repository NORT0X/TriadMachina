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

int main(int argc, char *argv[])
{

    std::string inputFile;
    std::string outputFile;

    // Check if there are enough arguments
    if (argc < 2)
    {
        std::cerr << "Usage: asembler [options] <input_filename>" << std::endl;
        return 1;
    }

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-o" && i + 1 < argc)
        {
            // Capture output file name
            outputFile = argv[++i];
        }
        else
        {
            // Assume the last argument is the input file name
            inputFile = arg;
        }
    }

    std::string fileName = inputFile;
    FILE *myFile = fopen(fileName.c_str(), "r");

    if (!myFile)
    {
        std::cout << "Couldn't open file " << fileName << std::endl;
        return -1;
    }

    if (outputFile.empty())
    {
        outputFile = changeExtensionToO(inputFile);
    }
    as = make_unique<Assembler>(outputFile);

    yyin = myFile;

    yyparse();

    std::cout << "Praser done!" << std::endl;
}
