#ifndef LAB_3_PIF_H
#define LAB_3_PIF_H

#include <stdio.h>

#define MAX_ENTRIES 10000

typedef struct PIFEntry {
    int tokenCode;
    int stPosition;
} PIFEntry; // create alias through typedef (to not have to write "struct PIFEntry" every time)

typedef struct PIF {
    PIFEntry entries[MAX_ENTRIES];
    int size;
} PIF;

// OBS: In C parameters are passed by value, aka the function receives a copy
// we use pointers so that we'll modfiy the original PIF and not only a copy of it
void pif_init(PIF *pif);

void pif_add(PIF *pif, int tokenCode, int stPosition);

void pif_print(const PIF *pif, FILE *output);


#endif
