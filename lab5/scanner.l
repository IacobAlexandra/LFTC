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
#include "automaton.h"

extern SymbolTable st;
extern PIF pif;

static Automaton identifierAutomaton;
static Automaton integerAutomaton;

/* Initialize both automaton's (before the scanner starts) */
/*      YY_USER_INIT = a place offered by Flex where u can initialize stuff before scanning */
#define YY_USER_INIT \
    init_identifier_automaton(&identifierAutomaton); \
    init_integer_automaton(&integerAutomaton);

%}

/* ------------ I. Define Candidate for Automaton ------------  */
/* this way the scanner also catches identifiers/constants, but it comes to the automaton to accept/reject it. */
CANDIDATE   [A-Za-z0-9_]+


%%

    /* ------------ II . Keywords, Operators, Separators ------------  */

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

    /* ------------ III. Identifiers, Constants  ------------  */

    /* in Lab 3: we let Regex decide whether the identifiers/constants were correct or not*/
    /* in Lab 5: we let the Automatons decide */

   {CANDIDATE} {
        // CASE 1: Accepted as Identifier
       if (automaton_accepts(&identifierAutomaton, yytext)) {
           /* Impose max length */
           if (yyleng > 256) {
               printf("Lexical error on line %d: identifier too long\n", yylineno);
           }
           else {
               int position = st_insert(&st, yytext);
               pif_add(&pif, IDENTIFIER_CODE, position);
               printf("IDENTIFIER: %s, ST position: %d\n", yytext, position);
           }
       }
       // CASE 2: Accepted as Integer
       else if (automaton_accepts(&integerAutomaton, yytext)) {
           int position = st_insert(&st, yytext);
           pif_add(&pif, CONSTANT_CODE, position);
           printf("CONSTANT: %s, ST position: %d\n", yytext, position);
       }
       // CASE 3: Rejected by both automatons
       else {
           printf("Lexical error on line %d: invalid token %s\n", yylineno, yytext);
       }
   }

    /* ------------ IV. Spaces, Wildcard chars:)  ------------  */

    /* Ignore space,tab, new line  they are not tokens.  ( + = one or more times) */
[ \t\r\n]+ {
}

    /* Reject any other single character (that is not an operator/smthng else) (. = any single character) */
. {
    printf("Lexical error on line %d: invalid character %s\n", yylineno, yytext);
}

%%