%{
    #include <cstdint>
    #include <iostream>
    #include <memory>

    #include "../inc/assembler/Assembler.hpp"
    #include "../inc/common/Elf.hpp"

    using namespace std;

    extern int yylex(void);
    extern int lineNum;
    extern unique_ptr<Assembler> as;
    
    void yyerror(const char *);
%}

%output "parser.cpp"
%defines "parser.hpp"

%union {
    uint32_t ival;
    uint8_t rval;
    char *sval;
}

%token <ival> LITERAL
%token <sval> SYMBOL
%token <sval> STRING
%token <rval> GPR CSR

%token GLOBAL EXTERN SECTION WORD SKIP ASCII EQU END
%token HALT INT IRET CALL RET JMP BEQ
%token BNE BGT PUSH POP XCHG ADD SUB
%token MUL DIV NOT AND OR XOR SHL SHR LD ST CSRRD CSRWR
%token ENDL

%left '+' '-'
%nonassoc UMINUS

%start program

%%

program:
        |
        statements { std::cout << "END\n"; }
        ;

statements:
        statement
        | statements statement
        ;

statement:
         label instruction ENDL
         | label directive ENDL
         | label ENDL
         | instruction ENDL
         | directive ENDL
         | ENDL
         ;

label:
        SYMBOL ':' { as->label($1); }
        ;

directive:
        GLOBAL global_args
        | EXTERN extern_args
        | SECTION SYMBOL                        { as->sectionDirective($2); }
        | WORD init_list
        | SKIP LITERAL                          { as->skipDirective($2); }
        | ASCII STRING                          { as->asciiDirective($2); }
        | EQU SYMBOL ',' ival_expr              { std::cout << "EQU " << $2 << "=" << "IVAL" << std::endl; }
        | END                                   { as->end(); }
        ;

instruction:
        HALT                                    { MInstruction instr(OPCODE::HALT, 0, 0, 0, 0 ,0); as->insertInstruction(instr); }
        | INT                                   { MInstruction instr(OPCODE::INT, 0, 0, 0, 0, 0); as->insertInstruction(instr); }
        | IRET                                  { as->iretInstruction();}
        | CALL LITERAL                          { as->callInstruction($2); }
        | CALL SYMBOL                           { as->callInstruction($2); }
        | RET                                   { MInstruction instr(OPCODE::LOAD, 3, PC, SP, 0, 4); as->insertInstruction(instr); }
        | JMP LITERAL                           { as->jmpInstruction($2); }
        | JMP SYMBOL                            { as->jmpInstruction($2); }
        | BEQ GPR ',' GPR ',' LITERAL           { as->branch($2, $4, $6, 0b0001); }
        | BEQ GPR ',' GPR ',' SYMBOL            { as->branch($2, $4, $6, 0b0001); }
        | BNE GPR ',' GPR ',' LITERAL           { as->branch($2, $4, $6, 0b0010); }
        | BNE GPR ',' GPR ',' SYMBOL            { as->branch($2, $4, $6, 0b0010); }
        | BGT GPR ',' GPR ',' LITERAL           { as->branch($2, $4, $6, 0b0011); }
        | BGT GPR ',' GPR ',' SYMBOL            { as->branch($2, $4, $6, 0b0011); }
        | PUSH GPR                              { MInstruction instr(OPCODE::STORE, 1, SP, 0, $2, -4); as->insertInstruction(instr); }
        | POP GPR                               { MInstruction instr(OPCODE::LOAD, 3, $2, 0x0E, 0, 4); as->insertInstruction(instr); }
        | XCHG GPR ',' GPR                      { MInstruction instr(OPCODE::XCHG, 0, 0, $4, $2, 0); as->insertInstruction(instr); }
        | ADD GPR ',' GPR                       { MInstruction instr(OPCODE::ARITHMETIC, 0, $4, $4, $2, 0); as->insertInstruction(instr); }
        | SUB GPR ',' GPR                       { MInstruction instr(OPCODE::ARITHMETIC, 1, $4, $4, $2, 0); as->insertInstruction(instr); }
        | MUL GPR ',' GPR                       { MInstruction instr(OPCODE::ARITHMETIC, 2, $4, $4, $2, 0); as->insertInstruction(instr);  }
        | DIV GPR ',' GPR                       { MInstruction instr(OPCODE::ARITHMETIC, 3, $4, $4, $2, 0); as->insertInstruction(instr); }
        | NOT GPR                               { MInstruction instr(OPCODE::LOGIC, 0, $2, $2, 0, 0); as->insertInstruction(instr); }
        | AND GPR ',' GPR                       { MInstruction instr(OPCODE::LOGIC, 1, $4, $4, $2, 0); as->insertInstruction(instr); }
        | OR GPR ',' GPR                        { MInstruction instr(OPCODE::LOGIC, 2, $4, $4, $2, 0); as->insertInstruction(instr); }
        | XOR GPR ',' GPR                       { MInstruction instr(OPCODE::LOGIC, 3, $4, $4, $2, 0); as->insertInstruction(instr); }
        | SHL GPR ',' GPR                       { MInstruction instr(OPCODE::SHIFT, 0, $4, $4, $2, 0); as->insertInstruction(instr); }
        | SHR GPR ',' GPR                       { MInstruction instr(OPCODE::SHIFT, 1, $4, $4, $2, 0); as->insertInstruction(instr); }
        | LD '$' LITERAL ',' GPR                { as->loadLiteral($3, $5, LiteralMode::VALUE); }
        | LD '$' SYMBOL ',' GPR                 { as->loadSymbol($3, $5, SymbolMode::VALUE); }
        | LD  LITERAL ',' GPR                   { as->loadLiteral($2, $4, LiteralMode::MEMORY); }
        | LD  SYMBOL ',' GPR                    { as->loadSymbol($2, $4, SymbolMode::MEMORY); }
        | LD  GPR ',' GPR                       { as->loadReg($2, $4, RegMode::REG_DIR); }
        | LD '[' GPR ']' ',' GPR                { as->loadReg($3, $6, RegMode::REG_IND); }
        | LD '[' GPR '+' LITERAL ']' ',' GPR    { as->loadRegLiteral($3, $5, $8); }
        | LD '[' GPR '+' SYMBOL ']' ',' GPR     { std::cout << "LD " << $3 << "+" << $5 << $8 << std::endl; }
        | ST GPR ',' LITERAL                    { as->storeLiteral($2, $4); }
        | ST GPR ',' SYMBOL                     { as->storeSymbol($2, $4); }
        | ST GPR ',' '[' GPR ']'                { as->storeReg($2, $5); }
        | ST GPR ',' '[' GPR '+' LITERAL ']'    { as->storeRegLiteral($2, $5, $7); }
        | ST GPR ',' '[' GPR '+' SYMBOL ']'     { std::cout << "ST " << $2 << " " << $5 << "+" << $7 << std::endl; }
        | CSRRD CSR ',' GPR                     { MInstruction instr(OPCODE::LOAD, 0, $4, $2, 0, 0); as->insertInstruction(instr); }
        | CSRWR GPR ',' CSR                     { MInstruction instr(OPCODE::LOAD, 4, $4, $2, 0, 0); as->insertInstruction(instr); }
        ;

init_list:
        SYMBOL                                  { as->wordDirectiveSymbol($1); }
        | LITERAL                               { as->wordDirectiveLiteral($1); }
        | init_list ',' SYMBOL                  { as->wordDirectiveSymbol($3); }
        | init_list ',' LITERAL                 { as->wordDirectiveLiteral($3); }
        ;

global_args:
        SYMBOL                                  { as->globalDirective($1); }
        | global_args ',' SYMBOL                { as->globalDirective($3); }
        ;

extern_args:
        SYMBOL                                  { as->externDirective($1); }
        | extern_args ',' SYMBOL                { as->externDirective($3); }
        ;

ival_expr:
         LITERAL                                { std::cout << "IVAL_EXPR " << $1 << std::endl; }
         | SYMBOL                               { std::cout << "IVAL_EXPR " << $1 << std::endl; }
         | ival_expr '+' ival_expr              { std::cout << "IVAL_EXPR +\n"; }
         | ival_expr '-' ival_expr              { std::cout << "IVAL_EXPR -\n"; }
         | '-' ival_expr %prec UMINUS           { std::cout << "UMINUS\n"; }
         | '(' ival_expr ')'                    { std::cout << "IVAL_EXPR ()\n"; }
         ;

%%

void yyerror(const char *s) {
    std::cout << "PARSER ERROR!\n"  << "Message: " << s << std::endl;
    exit(-1);
}
