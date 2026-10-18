#ifndef LAB_3_ST_H // Reminder: ifndef, define and endif are header guards they prevent the header from being included more than once
#define LAB_3_ST_H

#include <stdio.h>

// We represent the Symbol Table as a Binary Search Tree (BST)

typedef struct Node {
    char *symbol;
    int position; // position = the symbol's ID in the Symbol Table, used as a reference in the PIF
                            // it is assigned at insertion and it's independent of the node's actual location in the BST
    struct Node *left;
    struct Node *right;
} Node;

typedef struct SymbolTable {
    Node *root;
    int nextPosition;
} SymbolTable; // create alias through typedef (to not have to write struct SymbolTable every time)

void st_init(SymbolTable *st);

int st_find(const SymbolTable *st, const char *symbol);

int st_insert(SymbolTable *st, const char *symbol);

void st_print(const SymbolTable *st, FILE *output);

void st_destroy(SymbolTable *st);

#endif