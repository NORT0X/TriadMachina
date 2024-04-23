%{
    #include <iostream>
    #include <memory>

    #include "../Kit32.hpp"

    using namespace std;

    extern int yylex(void);
    extern int lineNum;
    
    void yyerror(const char *);
%}

%output "parser.cpp"
%defines "parser.hpp"

%union {
    u_int32_t ival;
    u_int8_t rval;
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
        SYMBOL ':' { std::cout << $1 << std::endl; }
        ;

directive:
        GLOBAL global_args
        | EXTERN extern_args
        | SECTION SYMBOL                        { std::cout << "SECTION" << " " << $2 << std::endl; }
        | WORD init_list
        | SKIP LITERAL                          { std::cout << "LITERAL " << $2 << std::endl; }
        | ASCII STRING                          { std::cout << "ASCII " << "$2" << std::endl; }
        | EQU SYMBOL ',' ival_expr              { std::cout << "EQU " << $2 << "=" << "IVAL" << std::endl; }
        | END
        ;

instruction:
        HALT                                    { std::cout << "HALT\n"; }
        | INT                                   { std::cout << "INT\n"; }
        | IRET                                  { std::cout << "IRET\n"; }
        | CALL LITERAL                          { std::cout << "CALL " << $2 << std::endl; }
        | CALL SYMBOL                           { std::cout << "CALL " << $2 << std::endl; }
        | RET                                   { std::cout << "RET\n"; }
        | JMP LITERAL                           { std::cout << "JMP " << $2 << std::endl; }
        | JMP SYMBOL                            { std::cout << "JMP " << $2 << std::endl; }
        | BEQ GPR ',' GPR ',' LITERAL           { std::cout << "BEQ " << $2 << " " << $4 << " " << $6 << std::endl; }
        | BEQ GPR ',' GPR ',' SYMBOL            { std::cout << "BEQ " << $2 << " " << $4 << " " << $6 << std::endl; }
        | BNE GPR ',' GPR ',' LITERAL           { std::cout << "BNE " << $2 << " " << $4 << " " << $6 << std::endl; }
        | BNE GPR ',' GPR ',' SYMBOL            { std::cout << "BNE " << $2 << " " << $4 << " " << $6 << std::endl; }
        | BGT GPR ',' GPR ',' LITERAL           { std::cout << "BGT " << $2 << " " << $4 << " " << $6 << std::endl; }
        | BGT GPR ',' GPR ',' SYMBOL            { std::cout << "BGT " << $2 << " " << $4 << " " << $6 << std::endl; }
        | PUSH GPR                              { std::cout << "PUSH " << $2 << std::endl; }
        | POP GPR                               { std::cout << "POP " << $2 << std::endl; }
        | XCHG GPR ',' GPR                      { std::cout << "XCHG " << $2 << " " << $4 << std::endl; }
        | ADD GPR ',' GPR                       { std::cout << "ADD " << $2 << " " << $4 << std::endl; }
        | SUB GPR ',' GPR                       { std::cout << "SUB " << $2 << " " << $4 << std::endl; }
        | MUL GPR ',' GPR                       { std::cout << "MUL " << $2 << " " << $4 << std::endl; }
        | DIV GPR ',' GPR                       { std::cout << "DIV " << $2 << " " << $4 << std::endl; }
        | NOT GPR                               { std::cout << "NOT " << $2 << std::endl; }
        | AND GPR ',' GPR                       { std::cout << "AND " << $2 << " " << $4 << std::endl; }
        | OR GPR ',' GPR                        { std::cout << "OR " << $2 << " " << $4 << std::endl; }
        | XOR GPR ',' GPR                       { std::cout << "XOR " << $2 << " " << $4 << std::endl; }
        | SHL GPR ',' GPR                       { std::cout << "SHL " << $2 << " " << $4 << std::endl; }
        | SHR GPR ',' GPR                       { std::cout << "SHR " << $2 << " " << $4 << std::endl; }
        | LD '$' LITERAL ',' GPR                { std::cout << "LD " << $3 << " " << $5 << std::endl; }
        | LD '$' SYMBOL ',' GPR                 { std::cout << "LD " << $3 << " " << $5 << std::endl; }
        | LD  LITERAL ',' GPR                   { std::cout << "LD " << $2 << " " << $4 << std::endl; }
        | LD  SYMBOL ',' GPR                    { std::cout << "LD " << $2 << " " << $4 << std::endl; }
        | LD  GPR ',' GPR                       { std::cout << "LD " << $2 << " " << $4 << std::endl; }
        | LD '[' GPR ']' ',' GPR                { std::cout << "LD " << $3 << " " << $6 << std::endl; }
        | LD '[' GPR '+' LITERAL ']' ',' GPR    { std::cout << "LD " << $3 << "+" << $5 << $8 << std::endl; }
        | LD '[' GPR '+' SYMBOL ']' ',' GPR     { std::cout << "LD " << $3 << "+" << $5 << $8 << std::endl; }
        | ST GPR ',' LITERAL                    { std::cout << "ST " << $2 << " " << $4 << std::endl; }
        | ST GPR ',' SYMBOL                     { std::cout << "ST " << $2 << " " << $4 << std::endl; }
        | ST GPR ',' '[' GPR ']'                { std::cout << "ST " << $2 << " " << $5 << std::endl; }
        | ST GPR ',' '[' GPR '+' LITERAL ']'    { std::cout << "ST " << $2 << " " << $5 << "+" << $7 << std::endl; }
        | ST GPR ',' '[' GPR '+' SYMBOL ']'     { std::cout << "ST " << $2 << " " << $5 << "+" << $7 << std::endl; }
        | CSRRD CSR ',' GPR                     { std::cout << "CSRRD " << $2 << " " << $4 << std::endl; }
        | CSRWR GPR ',' CSR                     { std::cout << "CSRWR " << $2 << " " << $4 << std::endl; }
        ;

init_list:
        SYMBOL                                  { std::cout << "INIT_LIST " << $1 << std::endl; }
        | LITERAL                               { std::cout << "INIT_LIST " << $1 << std::endl; }
        | init_list ',' SYMBOL                  { std::cout << "INIT_LIST " << $3 << std::endl; }
        | init_list ',' LITERAL                 { std::cout << "INIT_LIST " << $3 << std::endl; }
        ;

global_args:
        SYMBOL                                  { std::cout << "GLOBAL_ARGS " << $1 << std::endl; }
        | global_args ',' SYMBOL                { std::cout << "GLOBAL_ARGS " << $3 << std::endl; }
        ;

extern_args:
        SYMBOL                                  { std::cout << "EXTERN_ARGS " << $1 << std::endl; }
        | extern_args ',' SYMBOL                { std::cout << "EXTERN_ARGS " << $3 << std::endl; }
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
