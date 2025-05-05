#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdbool.h>

// Forward declarations
typedef struct Token Token;
typedef struct varState varState;

typedef enum {
    TOKEN_ID, TOKEN_NUM, TOKEN_ADD, TOKEN_SUB, TOKEN_MULTI, TOKEN_DIV,
    TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_WHILE, TOKEN_IF, TOKEN_EQUAL,
    TOKEN_THEN, TOKEN_DO, TOKEN_ELSE, TOKEN_END, TOKEN_ERROR,
    TOKEN_DECLARE, TOKEN_LESS, TOKEN_GREAT
} tokenType;

struct Token {
    tokenType type;
    char value[32];
    int position;
    int line;
};

// Only declarations here
extern Token* currentToken;
extern Token storeToken[256];
extern int tokenCount;
extern int positionChar;
extern int lineChar;
extern FILE* file;
extern varState* head;

#endif