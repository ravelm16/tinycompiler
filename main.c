#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "lexi.h"
#include "global.h"

int main(int argc, char *argv[]) {
    Token storeToken[256]={0}; /*declaring token stream here*/
    int tokenCount = 0;
    if (argc < 2)
    {
        printf("Please give source code input\n");
        return 0;
    }
    
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    while (true) {
        getNextToken(file);
        if ((storeToken[tokenCount - 1].type == TOKEN_END) || tokenCount >= 256) {
            break;
        }
    }

    printToken();
    fclose(file);
    return 0;
}
