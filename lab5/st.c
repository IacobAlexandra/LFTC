#include "st.h"
#include <stdlib.h>
#include <string.h>

void st_init(SymbolTable *st) {
    st->root = NULL;
    st->nextPosition = 1;
}

int st_find(const SymbolTable *st, const char *symbol) {
    const Node *current = st->root;

    // Traverse the BST
    while (current != NULL) {
        // Compare alphabetical order ( aka "lexicographical")
        int comparison = strcmp(symbol, current->symbol);

        if (comparison == 0) {
            return current->position;
        }
        //go to left child
        else if (comparison < 0) {
            current = current->left;
        }
        //go to right child
        else {
            current = current->right;
        }
    }

    return -1;
}

int st_insert(SymbolTable *st, const char *symbol) {
    Node *current = st->root;
    Node *parent = NULL; // to handle the scenario where we insert at the root

    // Traverse the BST to find: 1. its position OR 2. if it's not yet in the BST, its "future" parent
    while (current != NULL) {
        int comparison = strcmp(symbol, current->symbol);

        if (comparison == 0) {
            return current->position;
        }

        parent = current;

        if (comparison < 0){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }

    // Allocate memory for the node
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed.");
        exit(1);
    }
    // Allocate memory for the char* symbol
    node->symbol = malloc(strlen(symbol) + 1);
    if (node->symbol == NULL) {
        free(node);
        fprintf(stderr, "Memory allocation failed.");
        exit(1);
    }

    // Initialize the node
    strcpy(node->symbol, symbol);
    node->position = st->nextPosition++;
    node->left = NULL;
    node->right = NULL;

    // Attach the node to the tree
    if (parent == NULL) {
        st->root = node;
    }
    // Compare node's symbol with parent's symbol
    else if (strcmp(symbol, parent->symbol)<0) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }

    return node->position;
}


// Print Symbol Tree IN LEXICOGRAPHICAL ORDER
// Inorder DFS (~ left subtree -> current node -> right subtree ~,

static void print_nodes(const Node *node, FILE *output) {
    if (node == NULL) {
        return;
    }

    print_nodes(node->left, output);
    // Print to the output stream ( aka file or console)
        // %d = int (node->position)
        // %s = string (node->symbol)
    fprintf(output, "%d           %s\n", node->position, node->symbol);
    print_nodes(node->right, output);
}

void st_print(const SymbolTable *st, FILE *output) {
    fprintf(output, "Position   Symbol\n");
    print_nodes(st->root, output);
}

// Destroy Symbol Tree
// Postorder DFS (~ left subtree -> right subtree -> current node ~,
    // free the children before their parent), to not "lose any link to a child"
static void destroy_nodes(Node *node) {
    if (node == NULL) {
        return;
    }

    destroy_nodes(node->left);
    destroy_nodes(node->right);

    free(node->symbol);
    free(node);
}

void st_destroy(SymbolTable *st) {
    destroy_nodes(st->root);
    st->root = NULL;
    st->nextPosition = 1;
}