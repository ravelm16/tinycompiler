#ifndef PARSER_H
#define PARSER_H
#include "global.h"



typedef struct Atree Atree; 

struct Atree {
    nodeType type;
    int line;

    char* name; //for id
    int num; //for num
    char op; //for operator
    char* loopy; //for if or while statements
    

    Atree* left;
    Atree* right;
};

typedef struct
{
    Atree* statement;
    struct StmtList * next;

} StmtList;

typedef struct {
    Atree* base;
    StmtList* statements;
}Root;



void parser();
void statement();
void decl_stmt();
void if_stmt();
void while_stmt();
void exp_stmt();
void expression();
void variable();
void condition();



#endif



