#ifndef LEXI_H
#define LEXI_H

#include "global.h"

void getNextToken(FILE *fp);
void printToken();
int skipWhiteSpace(FILE *fp);
char* tokenDisplay(tokenType type);

#endif