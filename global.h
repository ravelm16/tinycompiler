#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>

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
    TOKEN_THEN,
    TOKEN_DO,
    TOKEN_ELSE,
    TOKEN_END,
    TOKEN_ERROR,
    TOKEN_DECLARE,
    
} tokenType;


typedef struct {
    tokenType type;
    char value[32];
    int position;
    int line;
} Token;

extern Token storeToken[256]; 
extern int tokenCount;  


#endif