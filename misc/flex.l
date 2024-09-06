%{
    #include <cstdint>
    #include "parser.hpp"
    #include <iostream>

    #include "../inc/common/Elf.hpp"

    using namespace std;

    extern int yyerror(const char *);
%}

%option outfile="flex.cpp" header-file="flex.hpp"

%option noyywrap

/* DIRECTIVES */

GLOBAL  ".global"
EXTERN  ".extern"
SECTION ".section"
WORD    ".word"
SKIP    ".skip"
ASCII   ".ascii"
EQU     ".equ"
END     ".end"

/* INSTRUCTIONS */

HALT    "halt"
INT     "int"
IRET    "iret"
CALL    "call"
RET     "ret"
JMP     "jmp"
BEQ     "beq"
BNE     "bne"
BGT     "bgt"
PUSH    "push"
POP     "pop"
XCHG    "xchg"
ADD     "add"
SUB     "sub"
MUL     "mul"
DIV     "div"
NOT     "not"
AND     "and"
OR      "or"
XOR     "xor"
SHL     "shl"
SHR     "shr"
LD      "ld"
ST      "st"
CSRRD   "csrrd"
CSRWR   "csrwr" 

/* REFERENCES */

GPR (%r1[0-5])|(%r[0-9])
SP "%sp"
PC "%pc"
CSR0 "%status"
CSR1 "%handler"
CSR2 "%cause"

LITERAL (0[Xx])?[0-9A-Fa-f]+
SYMBOL [A-Za-z_][A-Za-z0-9_]*
STRING \"(\\.|[^\"])*\"
COMMENT "#"[^\n\r]*

WHITESPACE [ \r\t]

%%

{WHITESPACE}    { /* SKIP */ }
{COMMENT}       { /* SKIP */ }
[-+()\[\]=.,:$] { return yytext[0]; }
\n              { return ENDL; }

{GLOBAL}        { return GLOBAL; }
{EXTERN}        { return EXTERN; }
{SECTION}       { return SECTION; }
{WORD}          { return WORD; }
{SKIP}          { return SKIP; }
{ASCII}         { return ASCII; }
{EQU}           { return EQU; }
{END}           { return END; }
{HALT}          { return HALT; }
{INT}           { return INT; }
{IRET}          { return IRET; }
{CALL}          { return CALL;}
{RET}           { return RET; }
{JMP}           { return JMP; }
{BEQ}           { return BEQ; }
{BNE}           { return BNE; }
{BGT}           { return BGT; }
{PUSH}          { return PUSH; }
{POP}           { return POP; }
{XCHG}          { return XCHG; }
{ADD}           { return ADD; }
{SUB}           { return SUB; }
{MUL}           { return MUL; }
{DIV}           { return DIV; }
{NOT}           { return NOT; }
{AND}           { return AND; }
{OR}            { return OR; }
{XOR}           { return XOR; }
{SHL}           { return SHL; }
{SHR}           { return SHR; }
{LD}            { return LD; }
{ST}            { return ST; }
{CSRRD}         { return CSRRD; }
{CSRWR}         { return CSRWR; }

{GPR}           { yylval.rval = atoi(yytext + 2); return GPR; }
{SP}            { yylval.rval = SP; return GPR; }
{PC}            { yylval.rval = PC; return GPR; }
{CSR0}          { yylval.rval = STATUS; return CSR; }
{CSR1}          { yylval.rval = HANDLER; return CSR; }
{CSR2}          { yylval.rval = CAUSE; return CSR; }

{LITERAL}       { yylval.ival = strtoul(yytext, NULL, 0); return LITERAL; }
{SYMBOL}        { yylval.sval = strdup(yytext); return SYMBOL; }
{STRING}        { yylval.sval = strdup(yytext); return STRING; }

.               { yyerror("Syntax error, no such symbol!"); }

%%
