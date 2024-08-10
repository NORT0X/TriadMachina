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
        SYMBOL ':' { std::cout << $1 << std::endl; as->label($1); }
        ;

directive:
        GLOBAL global_args
        | EXTERN extern_args
        | SECTION SYMBOL                        { std::cout << "SECTION" << " " << $2 << std::endl; as->sectionDirective($2); }
        | WORD init_list
        | SKIP LITERAL                          { std::cout << "LITERAL " << $2 << std::endl; as->skipDirective($2); }
        | ASCII STRING                          { std::cout << "ASCII " << "$2" << std::endl; }
        | EQU SYMBOL ',' ival_expr              { std::cout << "EQU " << $2 << "=" << "IVAL" << std::endl; }
        | END                                   { as->end(); }
        ;

instruction:
        HALT                                    { std::cout << "HALT\n"; as->haltInstruction(); }
        | INT                                   { std::cout << "INT\n"; as->intInstruction(); }
        | IRET                                  { std::cout << "IRET\n"; }
        | CALL LITERAL                          { std::cout << "CALL " << $2 << std::endl; as->callInstruction($2); }
        | CALL SYMBOL                           { std::cout << "CALL " << $2 << std::endl; as->callInstruction($2); }
        | RET                                   { std::cout << "RET\n"; as->popInstruction(15); }
        | JMP LITERAL                           { std::cout << "JMP " << $2 << std::endl; as->jmpInstruction($2); }
        | JMP SYMBOL                            { std::cout << "JMP " << $2 << std::endl; as->jmpInstruction($2); }
        | BEQ GPR ',' GPR ',' LITERAL           { std::cout << "BEQ " << $2 << " " << $4 << " " << $6 << std::endl; as->branch($2, $4, $6, 0b0001); }
        | BEQ GPR ',' GPR ',' SYMBOL            { std::cout << "BEQ " << $2 << " " << $4 << " " << $6 << std::endl; as->branch($2, $4, $6, 0b1001); }
        | BNE GPR ',' GPR ',' LITERAL           { std::cout << "BNE " << $2 << " " << $4 << " " << $6 << std::endl; as->branch($2, $4, $6, 0b0010); }
        | BNE GPR ',' GPR ',' SYMBOL            { std::cout << "BNE " << $2 << " " << $4 << " " << $6 << std::endl; as->branch($2, $4, $6, 0b1010); }
        | BGT GPR ',' GPR ',' LITERAL           { std::cout << "BGT " << $2 << " " << $4 << " " << $6 << std::endl; as->branch($2, $4, $6, 0b0011); }
        | BGT GPR ',' GPR ',' SYMBOL            { std::cout << "BGT " << $2 << " " << $4 << " " << $6 << std::endl; as->branch($2, $4, $6, 0b1011); }
        | PUSH GPR                              { std::cout << "PUSH " << $2 << std::endl; as->pushInstruction($2); }
        | POP GPR                               { std::cout << "POP " << $2 << std::endl; as->popInstruction($2); }
        | XCHG GPR ',' GPR                      { std::cout << "XCHG " << $2 << " " << $4 << std::endl; }
        | ADD GPR ',' GPR                       { std::cout << "ADD " << $2 << " " << $4 << std::endl; as->addInstruction($2, $4); }
        | SUB GPR ',' GPR                       { std::cout << "SUB " << $2 << " " << $4 << std::endl; as->subInstruction($2, $4); }
        | MUL GPR ',' GPR                       { std::cout << "MUL " << $2 << " " << $4 << std::endl; as->mulInstruction($2, $4); }
        | DIV GPR ',' GPR                       { std::cout << "DIV " << $2 << " " << $4 << std::endl; as->divInstruction($2, $4); }
        | NOT GPR                               { std::cout << "NOT " << $2 << std::endl; as->notInstruction($2); }
        | AND GPR ',' GPR                       { std::cout << "AND " << $2 << " " << $4 << std::endl; as->andInstruction($2, $4); }
        | OR GPR ',' GPR                        { std::cout << "OR " << $2 << " " << $4 << std::endl; as->orInstruction($2, $4); }
        | XOR GPR ',' GPR                       { std::cout << "XOR " << $2 << " " << $4 << std::endl; as->xorInstruction($2, $4); }
        | SHL GPR ',' GPR                       { std::cout << "SHL " << $2 << " " << $4 << std::endl; as->shlInstruction($2, $4); }
        | SHR GPR ',' GPR                       { std::cout << "SHR " << $2 << " " << $4 << std::endl; as->shrInstruction($2, $4); }
        | LD '$' LITERAL ',' GPR                { std::cout << "LD " << $3 << " " << $5 << std::endl; as->loadLiteral($3, $5, LiteralMode::VALUE); }
        | LD '$' SYMBOL ',' GPR                 { std::cout << "LD " << $3 << " " << $5 << std::endl; as->loadSymbol($3, $5, SymbolMode::VALUE); }
        | LD  LITERAL ',' GPR                   { std::cout << "LD " << $2 << " " << $4 << std::endl; as->loadLiteral($2, $4, LiteralMode::MEMORY); }
        | LD  SYMBOL ',' GPR                    { std::cout << "LD " << $2 << " " << $4 << std::endl; as->loadSymbol($2, $4, SymbolMode::MEMORY); }
        | LD  GPR ',' GPR                       { std::cout << "LD " << $2 << " " << $4 << std::endl; as->loadReg($2, $4, RegMode::REG_DIR); }
        | LD '[' GPR ']' ',' GPR                { std::cout << "LD " << $3 << " " << $6 << std::endl; as->loadReg($3, $6, RegMode::REG_IND); }
        | LD '[' GPR '+' LITERAL ']' ',' GPR    { std::cout << "LD " << $3 << "+" << $5 << $8 << std::endl; as->loadRegLiteral($3, $5, $8); }
        | LD '[' GPR '+' SYMBOL ']' ',' GPR     { std::cout << "LD " << $3 << "+" << $5 << $8 << std::endl; }
        | ST GPR ',' LITERAL                    { std::cout << "ST " << $2 << " " << $4 << std::endl; as->storeLiteral($2, $4); }
        | ST GPR ',' SYMBOL                     { std::cout << "ST " << $2 << " " << $4 << std::endl; as->storeSymbol($2, $4); }
        | ST GPR ',' '[' GPR ']'                { std::cout << "ST " << $2 << " " << $5 << std::endl; as->storeReg($2, $5); }
        | ST GPR ',' '[' GPR '+' LITERAL ']'    { std::cout << "ST " << $2 << " " << $5 << "+" << $7 << std::endl; as->storeRegLiteral($2, $5, $7); }
        | ST GPR ',' '[' GPR '+' SYMBOL ']'     { std::cout << "ST " << $2 << " " << $5 << "+" << $7 << std::endl; }
        | CSRRD CSR ',' GPR                     { std::cout << "CSRRD " << $2 << " " << $4 << std::endl; }
        | CSRWR GPR ',' CSR                     { std::cout << "CSRWR " << $2 << " " << $4 << std::endl; }
        ;

init_list:
        SYMBOL                                  { std::cout << "INIT_LIST " << $1 << std::endl; as->wordDirectiveSymbol($1); }
        | LITERAL                               { std::cout << "INIT_LIST " << $1 << std::endl; as->wordDirectiveLiteral($1); }
        | init_list ',' SYMBOL                  { std::cout << "INIT_LIST " << $3 << std::endl; as->wordDirectiveSymbol($3); }
        | init_list ',' LITERAL                 { std::cout << "INIT_LIST " << $3 << std::endl; as->wordDirectiveLiteral($3); }
        ;

global_args:
        SYMBOL                                  { std::cout << "GLOBAL_ARGS " << $1 << std::endl; as->globalDirective($1); }
        | global_args ',' SYMBOL                { std::cout << "GLOBAL_ARGS " << $3 << std::endl; as->globalDirective($3); }
        ;

extern_args:
        SYMBOL                                  { std::cout << "EXTERN_ARGS " << $1 << std::endl; as->externDirective($1); }
        | extern_args ',' SYMBOL                { std::cout << "EXTERN_ARGS " << $3 << std::endl; as->externDirective($3); }
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
