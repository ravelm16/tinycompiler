#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "global.h"
#include "parser.h"
#include "lexi.h"


/*********for checking the variable, is it declared or not *********/

void stateChecker(char* name) {
    varState* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            fprintf(stderr, "Error: Variable '%s' already declared\n", name);
            exit(EXIT_FAILURE);
        }
        current = current->next;
    }
}

void addVar(char* name, char* type) {
    stateChecker(name);
    
    varState* newVar = malloc(sizeof(varState));
    if (!newVar) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    newVar->name = strdup(name);
    newVar->type = strdup(type);
    newVar->next = head;
    head = newVar;
}
//////////////////////////////////////////////////////////////////



/*********checking the current status of the token whether its correct or not*********/
void expect(tokenType type) {
    if (!currentToken || currentToken->type != type) {
        fprintf(stderr, "Error: Expected token %s but got %s\n",
                tokenDisplay(type), tokenDisplay(currentToken ? currentToken->type : TOKEN_ERROR));
        exit(EXIT_FAILURE);
    }
    getNextToken(file);
}//////////////////////////////////////////////////////////////////////////////////



/*********to create the main root of the tree (program)*********/
Atree* createRoot() {
    Atree* root = malloc(sizeof(Atree));
    if (!root) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memset(root, 0, sizeof(Atree));
    root->type = NODE_PROGRAM;
    root->line = 0;
    root->left=root->right=root->mid=root->child=root->sibling = NULL;
    return root;
}
/////////////////////////////////////////////////////////////////



/*****generate statement for the program*****/
Atree* generateStatement() {
    Atree* stmt = malloc(sizeof(Atree));
    if (!stmt) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memset(stmt, 0, sizeof(Atree));
    stmt->child = createStatement();
    return stmt;
}
//////////////////////////////////////////////



/**/
Atree* createStatement() {
    if (!currentToken) {
        fprintf(stderr, "Error: Unexpected end of input\n");
        exit(EXIT_FAILURE);
    }
    
    switch (currentToken->type) {
        case TOKEN_DECLARE: return declare_statement();
        case TOKEN_IF: return if_stmt();
        case TOKEN_WHILE: return while_stmt();
        case TOKEN_ID: return expression_stmt();
        default:
            fprintf(stderr, "Error: Unexpected token %s\n", tokenDisplay(currentToken->type));
            exit(EXIT_FAILURE);
    }
}


Atree* vari() {
    // Handle parentheses case
    if (currentToken->type == TOKEN_LPAREN) {
        expect(TOKEN_LPAREN);
        Atree* exp = NULL;  // Placeholder for future expression handling
        expect(TOKEN_RPAREN);
        return exp;
    }
    // Handle identifier case
    else if (currentToken->type == TOKEN_ID) {
        Atree* variable = malloc(sizeof(Atree));
        if (!variable) {
            fprintf(stderr, "Error: Memory allocation failed in vari() for ID\n");
            exit(EXIT_FAILURE);
        }
        memset(variable, 0, sizeof(Atree));  // Zero-initialize the entire struct
        
        variable->type = NODE_VAR;
        variable->typeToken = currentToken->type;
        
        // Safer string copying
        if (currentToken->value) {
            variable->data.name = strdup(currentToken->value);
            if (!variable->data.name) {
                fprintf(stderr, "Error: Failed to duplicate string in vari()\n");
                free(variable);
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Error: Token value is NULL in vari()\n");
            free(variable);
            exit(EXIT_FAILURE);
        }
        
        expect(TOKEN_ID);
        return variable;
    }
    // Handle number case
    else if (currentToken->type == TOKEN_NUM) {
        Atree* variable = malloc(sizeof(Atree));
        if (!variable) {
            fprintf(stderr, "Error: Memory allocation failed in vari() for NUM\n");
            exit(EXIT_FAILURE);
        }
        memset(variable, 0, sizeof(Atree));  // Zero-initialize
        
        variable->type = NODE_VAR;
        variable->typeToken = currentToken->type;
        
        // Handle numeric value
        if (currentToken->value) {
            variable->data.name = strdup(currentToken->value);
            if (!variable->data.name) {
                fprintf(stderr, "Error: Failed to duplicate number string\n");
                free(variable);
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Error: Numeric token has NULL value\n");
            free(variable);
            exit(EXIT_FAILURE);
        }
        
        expect(TOKEN_NUM);
        return variable;
    }
    // Handle unexpected token case
    else {
        fprintf(stderr, "Error: Unexpected token %s in vari()\n", 
                tokenDisplay(currentToken->type));
        exit(EXIT_FAILURE);
    }
}


Atree* declare_statement() {
    Atree* statement = malloc(sizeof(Atree));
    if(!statement) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memset(statement, 0, sizeof(Atree)); 
    statement->type = NODE_DECL_STMT;

    // Get variable type (int/char)
     char* variableType = tokenDisplay(currentToken->type);
    expect(currentToken->type);

    // Get variable name
    char* variableName = currentToken->value;
    addVar(variableName, variableType);
    statement->left = vari();
    
    // Check for optional initialization
    if(currentToken->type == TOKEN_EQUAL) {
        statement->data.op = currentToken->value;
        expect(TOKEN_EQUAL);
        statement->right = vari();
    }
    
    // Handle newline or end of declaration
    if(currentToken->type == TOKEN_END) {
        return statement;
    }
    
    return statement;
}

Atree* expression_stmt() {
    Atree* node = malloc(sizeof(Atree));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memset(node, 0, sizeof(Atree));
    node->type = NODE_EXP_STMT;
    
    node->left = vari();
    expect(TOKEN_EQUAL);
    
    node->right = expressionP();
    return node;
}

Atree* expressionP() {
    Atree* exp = vari();
    
    if (currentToken->type == TOKEN_SUB || currentToken->type == TOKEN_ADD || 
        currentToken->type == TOKEN_MULTI || currentToken->type == TOKEN_DIV) {
        
        Atree* expression = malloc(sizeof(Atree));
        if (!expression) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        memset(expression, 0, sizeof(Atree));
        
        expression->type = NODE_EXP;
        expression->data.op = strdup(currentToken->value); // Copy the operator
        expect(currentToken->type);
        
        expression->left = exp;
        expression->right = expressionP();
        return expression;
    }
    return exp;
}

Atree* if_stmt(){
    Atree* ifstmt = malloc(sizeof(Atree));
    ifstmt->type = NODE_IF_STMT;
    expect(TOKEN_IF);
    ifstmt->left = condition();
    expect(TOKEN_THEN);
    ifstmt->mid = createStatement();

    if(currentToken->type == TOKEN_ELSE){
        expect(TOKEN_ELSE);
        ifstmt->right = createStatement();

    }

    return ifstmt;

}

Atree* while_stmt(){
    Atree* whilestmt = malloc(sizeof(Atree));
    whilestmt->type = NODE_WHILE_STMT;
    expect(TOKEN_WHILE);
    whilestmt->left = condition();
    expect(TOKEN_DO);
    whilestmt->right = createStatement();
    return whilestmt;
}

Atree* condition(){
    expect(TOKEN_LPAREN);
    Atree* left_var = vari();

    char* op = currentToken->value;
    if(currentToken->type == TOKEN_GREAT || currentToken->type == TOKEN_LESS){
        expect(currentToken->type);

    } else {
        printf("wrong operator\n");
        exit(1);
    }

    Atree* right_var = vari();
    expect(TOKEN_RPAREN);
    Atree* condition = malloc(sizeof(Atree));
    condition->type = NODE_COND;
    condition->data.op = op;
    condition->left = left_var;
    condition->right = right_var;
    return condition;

}


void pushStatement(Atree** head, Atree* statement) {
    if (!statement) {
        fprintf(stderr, "Error: Cannot push NULL statement\n");
        return;
    }
    
    // Initialize the new node's sibling
    statement->sibling = NULL;

    // Handle empty list case
    if (!*head) {
        *head = statement;
        return;
    }

    // Find the last node
    Atree* current = *head;
    while (current->sibling != NULL) {
        current = current->sibling;
    }
    
    // Append the new statement
    current->sibling = statement;
}



void printTree(Atree* Root, int level) {

    if (Root == NULL) return;

    // Print indentation based on level
    int i = 0;
    while(i<level-1){

        printf("  ");
        i++;
    }




    
    switch (Root->type) {

        case NODE_PROGRAM:
    
            break;
        case NODE_DECL_STMT:
            printf("|--");
            printf(">Declaration Statement\n");
            
            break;
        case NODE_IF_STMT:
            printf("|--");
            printf(">If Statement\n");
            
            break;
        case NODE_WHILE_STMT:
        printf("|--");
            printf(">While Statement\n");
            
            break;
        case NODE_EXP_STMT:
        printf("|--");
            printf(">Expression Statement\n");
            
            break;
        case NODE_EXP:
        printf("|--");
            printf(">Expression: Operator '%s'\n", Root->data.op);
            
            break;
        case NODE_VAR:
            if (Root->typeToken == TOKEN_ID) {
                printf("|--");
                printf(">Variable: %s\n", Root->data.name);
                
            } else if (Root->typeToken == TOKEN_NUM) {
                printf("|--");
                printf(">Number: %s\n", Root->data.name);
                
            }
            break;
        case NODE_COND:
        printf("|--");
            printf(">Condition: Operator '%s'\n", Root->data.op);
            break;
        default:
        printf("|--");
            printf(">Unknown Node Type\n");
    }

    if (Root->left != NULL) {
        printTree(Root->left, level + 1);
    }
    if (Root->mid != NULL) {
        printTree(Root->mid, level + 1);
    }
    if (Root->right != NULL) {
        printTree(Root->right, level + 1);
    }
    if (Root->child != NULL) {
        printTree(Root->child, level + 1);
    }
        
    if (Root->sibling != NULL) {
        printTree(Root->sibling, level);
    }
}
