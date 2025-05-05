#ifndef PARSER_H
#define PARSER_H

#include "global.h"


typedef enum {
    NODE_PROGRAM, NODE_DECL_STMT, NODE_IF_STMT, NODE_WHILE_STMT,
    NODE_EXP_STMT, NODE_EXP, NODE_VAR, NODE_COND
} nodeType;

typedef struct Atree {
    nodeType type;
    tokenType typeToken;
    union {
        char* name;
        char* op;
        char* loopy;
    } data;
    int line;
    struct Atree *left, *right, *mid, *child, *sibling;
} Atree;

typedef struct varState {
    char* name;
    char* type;
    int state;
    struct varState* next;
} varState;

 varState* head;

// Function declarations
void stateChecker(char* name);
void addVar(char* name, char* type);
void expect(tokenType type);
void pushStatement(Atree** head, Atree* statement);
Atree* createStatement();
Atree* vari();
Atree* declare_statement();
Atree* expression_stmt();
Atree* expressionP();
Atree* if_stmt();
Atree* while_stmt();
Atree* condition();
Atree* createRoot();
Atree* generateStatement();
void printTree(Atree* Root, int level);

#endif