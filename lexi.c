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
        case TOKEN_WHILE:return 'WHILE';
        case TOKEN_EQUAL:return 'EQUAL';
        case TOKEN_IF:return 'IF';
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
    currentToken->value[32] = '\0';
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
        char checker[10] = {0};
        int i = 0;

        while(isalpha(character)&& character !=EOF && !isspace(character))
        {
            checker[i] = (char)character;
            i++;
            character = fgetc(fp);
        }
        
        if(character != EOF){
            ungetc(character, fp);

        }
        
        if(strcmp(checker, "if")==0){
            currentToken->type = TOKEN_IF;
        }

        else if (strcmp(checker, "while")==0){
            currentToken->type = TOKEN_WHILE;
        }

        else currentToken->type = TOKEN_ID;
        
        strncpy(currentToken->value, checker, sizeof((currentToken->value)-1));
        currentToken->value[sizeof((currentToken->value)-1)] = '\0';
    } 
    
    
    
    
    else if (isdigit(character)) {
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


