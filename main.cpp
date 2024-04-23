#include <cstdio>
#include <iostream>

#include <stdio.h>
#include <string>

using namespace std;
extern int yylex(void);
extern int yyparse();
extern FILE* yyin;

int main()
{
    std::string fileName = "test.as";
    FILE* myFile = fopen(fileName.c_str(), "r");

    if (!myFile) {
        std::cout << "Couldn't open file " << fileName << std::endl;
        return -1;
    }

    yyin = myFile;

    yyparse();

    std::cout << "Praser done!" << std::endl;
}
