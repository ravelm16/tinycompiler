#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "lexi.h"
#include "global.h"
#include "parser.h"

Token* currentToken = NULL;
Token storeToken[256];
int tokenCount = 0;
int positionChar = 1;
int lineChar = 1;
FILE* file = NULL;
varState* head = NULL; 
Atree* myProgram = NULL;
Atree* currentStatement = NULL;

void freeAST(Atree* node){
    if (!node) return;
    
    freeAST(node->left);
    freeAST(node->right);
    freeAST(node->mid);
    freeAST(node->child);
    freeAST(node->sibling);
    
    if (node->data.name) free(node->data.name);
    free(node);
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please give source code input\n");
        return 0;
    }
    
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    Atree* myProgram = createRoot();
    while (true) {
        getNextToken(file);
        if (currentToken == NULL || currentToken->type == TOKEN_END || tokenCount >= 256)
            break;
        
        Atree* currentStatement = generateStatement();
        pushStatement(&myProgram->child, currentStatement);
    }



   

    printToken();
    printf("\nParse Tree:\n");
    printTree(myProgram, 0);
    freeAST(myProgram);
    fclose(file);
    return 0;
}   