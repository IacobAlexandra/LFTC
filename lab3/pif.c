// NOTE: PIF keeps each occurrence of a token, in the program's order
//in comparison with the Symbol Table (ST), which doesn't keep duplicates
// PIF entry = (token code, position in ST)
                // token code = what type of token it is ( we use code just for convetion, could've used words as well)
                // position in ST = which of the identifiers/constants it is
#include "pif.h"
#include <stdlib.h>

void pif_init(PIF *pif) {
    pif->size = 0;
}

void pif_add(PIF *pif, int tokenCode, int stPosition) {
    // Check if PIF is full
    if(pif->size >= MAX_ENTRIES) {
        fprintf(stderr, "PIF capacity exceeded.\n");
        exit(1);
    }

    // Add the pair at the end
    pif->entries[pif->size].tokenCode = tokenCode;
    pif->entries[pif->size].stPosition = stPosition;
    pif->size++;
}

void pif_print(const PIF *pif, FILE *output) {
    fprintf(output, "Token code   ST position\n");

    for (int i=0; i < pif->size; i++) {
        fprintf(output, "%d             %d\n", pif->entries[i].tokenCode, pif->entries[i].stPosition);
    }
}