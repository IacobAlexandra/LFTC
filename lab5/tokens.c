#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 100
#define TOKEN_LENGTH 32

// Save the list of tokens from "tokens.txt"
static char tokens[MAX_TOKENS][TOKEN_LENGTH];
static int tokenCount = 0;

void load_tokens(const char *filename) {
    FILE *file = fopen(filename, "r"); // filename = "tokens.txt"

    if (file == NULL) {
        perror("Cannot open token list");
        exit(1);
    }

    tokenCount = 0;
    char token[TOKEN_LENGTH];

    // Read the fixed tokens in file order
    while (fscanf(file, "%s", token) == 1) { // NOTE: fscanf() returns the nr of values. We ask for only 1 word, so 1 is what we are expecting
        strcpy(tokens[tokenCount++], token);
    }

    fclose(file);
}

// Given a token, it compares the fixed token list and returns the code ( i + 2 , i being its positio in the array)
// Codes 0 and 1 are reserved for identifiers and constants
int token_code(const char *token) {
    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(tokens[i], token) == 0) {
            return i + 2;
        }
    }

    return -1;
}