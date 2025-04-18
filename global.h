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
    TOKEN_LESS,
    TOKEN_GREAT,
    
} tokenType;

typedef enum {
    NODE_PROGRAM,
    NODE_DECL_STMT,
    NODE_EXPR_STMT,
    NODE_WHILE_STMT,
    NODE_EXP_STMT,
    NODE_EXP,
    NODE_VAR,
    NODE_COND, 
} nodeType;

typedef struct {
    tokenType type;
    char value[32];
    int position;
    int line;
    nodeType node;
} Token;

extern Token* currentToken;
extern Token storeToken[256]; /*this is an extern global struct array called storeToken belonging in a header called global.h*/
extern int tokenCount; 





#endif