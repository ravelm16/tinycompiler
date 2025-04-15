#ifndef LEXI_H
#define LEXI_H
#include <stdio.h>
#include "global.h"

typedef enum {
    TOKEN_ID,
    TOKEN_NUM,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MULTI,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_WHILE,
    TOKEN_IF,
    TOKEN_EQUAL,
    TOKEN_END,
    TOKEN_ERROR,
    
} tokenType;


typedef struct {
    tokenType type;
    char value[32];
    int position;
} Token;

extern Token storeToken[256]; 
extern int tokenCount;   

const char* tokenDisplay(tokenType type);
void getNextToken(FILE *fp);
void printToken();
int skipWhiteSpace(FILE *fp);

#endif