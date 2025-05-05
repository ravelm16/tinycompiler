#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "global.h"
#include "lexi.h"




char* tokenDisplay(tokenType type) {
    switch (type) {
        case TOKEN_ID:    return "ID";
        case TOKEN_NUM:   return "NUM";
        case TOKEN_ADD:   return "ADD";
        case TOKEN_SUB:   return "SUB";
        case TOKEN_MULTI: return "MULTI";
        case TOKEN_DIV:   return "DIV";
        case TOKEN_LPAREN:return "LPAREN";
        case TOKEN_RPAREN:return "RPAREN";
        case TOKEN_WHILE:return "WHILE";
        case TOKEN_EQUAL:return "EQUAL";
        case TOKEN_IF:return "IF";
        case TOKEN_ELSE: return "ELSE";
        case TOKEN_DO: return "DO";
        case TOKEN_THEN: return "THEN";
        case TOKEN_END:   return "END";
        case TOKEN_ERROR: return "ERROR";
        case TOKEN_DECLARE: return "DECLARE";
        case TOKEN_LESS: return "LESS";
        case TOKEN_GREAT: return "GREAT";
        default:         return "UNKNOWN";
    }
}

int skipWhiteSpace(FILE *fp) {
    int character;
    while ((character = fgetc(fp)) != EOF) {
        if (!isspace(character)) {
      
            return character;
        } else if (character == '\n'){
            lineChar++;
            positionChar = 1;
            return character;
        }
    }
    return EOF;
}

void getNextToken(FILE *fp) {
    
    currentToken = &storeToken[tokenCount]; //declaring currentToken
    memset(currentToken->value, 0, sizeof(currentToken->value));
    currentToken->position = positionChar;
    currentToken->line = lineChar;
    

    int character = skipWhiteSpace(fp);

    if (character == EOF) {
        currentToken->type = TOKEN_END;
        tokenCount++;
        return;
    }

    if (character == '\n'){
        return;
    }
    positionChar++;  

    if (isalpha(character)) {
        char checker[32] = {0};
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
         else if (strcmp(checker, "do")==0)
         {
            currentToken->type = TOKEN_DO;
         }
         
         else if (strcmp(checker, "then")==0){
            currentToken->type = TOKEN_THEN;
         }
         else if (strcmp(checker, "else")== 0){
            currentToken->type = TOKEN_ELSE;
         }
         else if (strcmp(checker, "int") == 0 | strcmp(checker, "char") == 0)
         {
            currentToken->type = TOKEN_DECLARE;
         }
         
        else currentToken->type = TOKEN_ID;
        
        strncpy(currentToken->value, checker, 6);
        currentToken->value[6] = '\0';
    } 
    
    
    
    
    else if (isdigit(character)) 
    {
        char checker[32]={0};
        int i = 0;

        while(isdigit(character) && character != EOF && !isspace(character))
        {
            checker[i]= (char)character;
            i++;
            character = fgetc(fp);
        }
        if(character != EOF){
            ungetc(character, fp);

        }
        currentToken->type = TOKEN_NUM;
        strncpy(currentToken->value, checker, 6);
        currentToken->value[6] = '\0';
        
    } 
    else 
    {
        switch (character)
        {
            case '+': currentToken->type = TOKEN_ADD; break;
            case '-': currentToken->type = TOKEN_SUB; break;
            case '*': currentToken->type = TOKEN_MULTI; break;
            case '/': currentToken->type = TOKEN_DIV; break;
            case '(': currentToken->type = TOKEN_LPAREN; break;
            case ')': currentToken->type = TOKEN_RPAREN; break;
            case '=': currentToken->type = TOKEN_EQUAL; break;
            case '<': currentToken->type = TOKEN_LESS; break;
            case '>': currentToken->type = TOKEN_GREAT; break;
            default:  currentToken->type = TOKEN_ERROR; break;
        }
        currentToken->value[0] = (char)character;
        currentToken->value[1]='\0';
    }
    tokenCount++;
}

void printToken() {
    for (int i = 0; i < tokenCount; i++) {
        printf("<%d | %d | %s | %s>\n",
               storeToken[i].line, storeToken[i].position,
               tokenDisplay(storeToken[i].type),
               storeToken[i].value);
    }
}


