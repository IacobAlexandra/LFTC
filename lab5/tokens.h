#ifndef LAB_3_TOKENS_H
#define LAB_3_TOKENS_H

#define IDENTIFIER_CODE 0
#define CONSTANT_CODE 1

void load_tokens(const char *filename);

int token_code(const char *token);

#endif
