#ifndef LEXI_H
#define LEXI_H
#include <stdio.h>
#include "global.h"
#define MAXLENGTH 32


const char* tokenDisplay(tokenType type);
void getNextToken(FILE *fp);
void printToken();
int skipWhiteSpace(FILE *fp);

#endif