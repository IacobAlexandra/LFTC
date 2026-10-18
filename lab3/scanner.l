/* = stop at EOF without requiring a yywrap() function. */
%option noyywrap
/* = nounistd: avoid including unistd.h, for Windows compatibility. */
%option nounistd
/* = track line numbers for error messages. */
%option yylineno
/* = we always read from a file */
%option never-interactive

%{
    /* for printf */
#include <stdio.h>
#include "st.h"
#include "pif.h"
#include "tokens.h"

extern SymbolTable st;
extern PIF pif;
%}

/* ------------ I. Reusable regex definitions ------------  */
LETTER      [A-Za-z]
DIGIT       [0-9]
IDENTIFIER  {LETTER}({LETTER}|{DIGIT}|_)*
INTEGER     0|[1-9]{DIGIT}*

/* OBS for UNSIGNED integers -> "-12" = "-"(operator) + "12"(constant) => 2 tokens */

%%

    /* ------------ II . Rules to match  ------------  */

    /* yytext  = matched text. Flex chooses the longest match */

"int"|"read"|"print"|"if"|"else"|"while"|"in"|"not"|"between"|"is"|"unique" {
    pif_add(&pif, token_code(yytext), 0);
    printf("KEYWORD: %s\n", yytext);
}

"=="|"!="|"<="|">="|"="|"<"|">"|"+"|"-"|"*"|"/"|"%" {
    pif_add(&pif, token_code(yytext), 0);
    printf("OPERATOR: %s\n", yytext);
}

";"|","|"("|")"|"["|"]"|"{"|"}" {
    pif_add(&pif, token_code(yytext), 0);
    printf("SEPARATOR: %s\n", yytext);
}

    /* ------------ III. Lexical Conventions  ------------  */

    /* 1. Reject digits followed by letters/symbols (ex. 12arv -> ERROR) */
{DIGIT}+[A-Za-z_][A-Za-z0-9_]* {
    printf("Lexical error on line %d: invalid token %s\n",yylineno, yytext);
    /*  yylineno = line number */
}

    /* 2. Reject numbers with leading zeros (ex. 001 -> ERROR) */
0{DIGIT}+ {
    printf("Lexical error on line %d: leading zeros in %s\n", yylineno, yytext);
}

    /* ------------ IV. Identifiers, Constants  ------------  */

    /* Recognize identifiers */
{IDENTIFIER} {
    /*impose max lenth */
    if (yyleng > 256) {
        printf("Lexical error on line %d: identifier too long\n", yylineno);
    }
    else {
        int position = st_insert(&st, yytext);
        pif_add(&pif, IDENTIFIER_CODE, position);
        printf("IDENTIFIER: %s, ST position: %d\n", yytext, position);
    }
}

    /*  Recognize constants */
{INTEGER} {
     int position = st_insert(&st, yytext);
     pif_add(&pif, CONSTANT_CODE, position);
     printf("CONSTANT: %s, ST position: %d\n",yytext, position);
}

    /* ------------ V. Miscellanous  ------------  */

    /* Ignore space,tab, new line  they are not tokens.  ( + = one or more times) */
[ \t\r\n]+ {
}

    /* Reject any other single character (that is not an operator/smthng else) (. = any single character) */
. {
    printf("Lexical error on line %d: invalid character %s\n", yylineno, yytext);
}

%%