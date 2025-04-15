#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "global.h"
#include "lexi.h"


const char* tokenDisplay(tokenType type) {
    switch (type) {
        case TOKEN_ID:    return "ID";
        case TOKEN_NUM:   return "NUM";
        case TOKEN_ADD:   return "ADD";
        case TOKEN_SUB:   return "SUB";
        case TOKEN_MULTI: return "MULTI";
        case TOKEN_DIV:   return "DIV";
        case TOKEN_LPAREN:return "LPAREN";
        case TOKEN_RPAREN:return "RPAREN";
        case TOKEN_END:   return "END";
        case TOKEN_ERROR: return "ERROR";
        default:         return "UNKNOWN";
    }
}



Token storeToken[256]={0};
int tokenCount = 0;
int positionChar = 1;

int skipWhiteSpace(FILE *fp) {
    int character;
    while ((character = fgetc(fp)) != EOF) {
        if (!isspace(character)) {
      
            return character;
        }
    }
    return EOF;
}

void getNextToken(FILE *fp) {

    Token *currentToken = &storeToken[tokenCount];
    currentToken->value = '\0';
    currentToken->position = positionChar;

    int character = skipWhiteSpace(fp);

    if (character == EOF) {
        currentToken->type = TOKEN_END;
        tokenCount++;
        return;
    }

    currentToken->value = (char)character;
    positionChar++;  

    if (isalpha(character)) {
        currentToken->type = TOKEN_ID;
    } else if (isdigit(character)) {
        currentToken->type = TOKEN_NUM;
    } else {
        switch (character) {
            case '+': currentToken->type = TOKEN_ADD; break;
            case '-': currentToken->type = TOKEN_SUB; break;
            case '*': currentToken->type = TOKEN_MULTI; break;
            case '/': currentToken->type = TOKEN_DIV; break;
            case '(': currentToken->type = TOKEN_LPAREN; break;
            case ')': currentToken->type = TOKEN_RPAREN; break;
            default:  currentToken->type = TOKEN_ERROR; break;
        }
    }
    tokenCount++;
}

void printToken() {
    for (int i = 0; i < tokenCount; i++) {
        printf("%d | %s | %c\n",
               storeToken[i].position,
               tokenDisplay(storeToken[i].type),
               storeToken[i].value);
    }
}


