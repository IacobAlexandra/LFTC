#include <stdio.h>
#include "st.h"
#include "pif.h"
#include "tokens.h"

extern FILE *yyin;
int yylex(void);

SymbolTable st;
PIF pif;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Args missing");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("Cannot open source file");
        return 1;
    }

    load_tokens("tokens.txt");
    st_init(&st);
    pif_init(&pif);

    yylex();

    printf("\nSymbol Table:\n");
    st_print(&st, stdout);

    printf("\nPIF:\n");
    pif_print(&pif, stdout);

    fclose(yyin);
    st_destroy(&st);

    return 0;
}