#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "lexi.h"
#include "global.h"

int main() {


    FILE *file = fopen("example.txt", "r");

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
