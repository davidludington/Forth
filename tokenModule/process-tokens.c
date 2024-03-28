#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "token.h"
#include "dictionary.h"


static struct {
    char* name;
    stack_operation func;
} operations[] = {
    {"+", stack_add},
    {"-", stack_sub},
    {"*", stack_mult},
    {"/", stack_div},
    {"dup", stack_dup},
    {"drop", stack_drop},
    {"swap", stack_swap},
    {"over", stack_over},
    {"rot", stack_rot},
    {"2drop", two_drop},
    {"2swap", two_swap},
    {"2over", two_over},
    {"2dup", two_dup},
    {NULL, NULL}
};

void execute_stack_operation(Stack* stack, char* operation) {
    for (int i = 0; operations[i].name != NULL; i++) {
        if (strcmp(operation, operations[i].name) == 0) {
            operations[i].func(stack);
            return 1;
        }
    }
    // Operation not found
    return 0;
}


// add number to stack
void processNumber(stack_i* stack, struct token_t token){
    int num_int = atoi(token.text);
    // just push number to stack
    stack_push(stack, num_int);
}

// symbols help add variables
void processSymbol(stack_i* stack, struct token_t token, int* varDec){
    
    if (strcmp(token.text, ":") == 0) {
        // initilize valiable decleration
        *varDec = 1;
    }
}

// processing words
void processWord(stack_i* stack, struct token_t token, struct dictionary dict){
    if (strcmp(token.text, "dup") == 0) {
        stack_dup(stack);
    } else if (strcmp(token.text, "drop") == 0) {
        stack_drop(stack);
    } else if (strcmp(token.text, "swap") == 0) {
        stack_swap(stack);
    } else if (strcmp(token.text, "over") == 0) {
        stack_over(stack);
    }else if (strcmp(token.text, "rot") == 0) {
        stack_rot(stack);
    }else if (strcmp(token.text, "2drop") == 0) {
        two_drop(stack);
    } else if (strcmp(token.text, "2swap") == 0) {
        two_swap(stack);
    } else if (strcmp(token.text, "2over") == 0) {
        two_over(stack);
    }
    else if (strcmp(token.text, "2dup") == 0) {
        two_dup(stack);
    }
    // if none of these are true then check the dictionary
    else {
        //if it is in the dictionary
        struct token_t *tokens = get_dictionary_item(dict, token.text);
        if (tokens != NULL) {
            // Process the tokens if they are found
            process_to_stack(stack, tokens, dict);
        } else {
            // Handle the case when the text is not found in the dictionary
            // no variable by that name
        }

    }
    // if none there then ?
}


void pushValesToVar(struct token_t* varValues, struct token_t token, int* varSize){
    varValues[*varSize] = token; // Dereference varSize to get the integer value
    *varSize = *varSize + 1; // Increment the size after adding the token
    varValues = realloc(varValues, (*varSize) * sizeof(struct token_t)); // Update the reallocated size
}

void handleVariableDecleration(int* variableDecleration, int* varSize, char* varName, struct token_t token, 
struct token_t* varValues, struct dictionary dict){
    //check if it is the first word
    
    if(*varSize == 0){
        // first word = varName
        varName = token.text;
    }else if(strcmp(token.text, ";") == 0){
        // end the var decleration
        //add the var to the dictionary
        add_dictionary_item(dict, varName, varValues);
        //reset all var helpers
        *varSize = 0;
        *variableDecleration = 0;
        free(varValues);
    }else{
        // add tokens that will be part of the var
        pushValesToVar(varValues, token, varSize);
    }
}

// manipulates stack based on token
void process_to_stack(stack_i* stack, struct token_t* tokens, struct dictionary dictionary){
    
    int numTokens = 0;

    // for variable decleration
    int variableDecleration = 0;
    int varSize = 0;
    char* varName;

    struct token_t* varValues = malloc(sizeof(struct token_t));


    //cycle through tokens
    while (tokens[numTokens].text != NULL) {

        
        if(variableDecleration == 1){ // this token is part of a var decletation
            handleVariableDecleration(&variableDecleration, &varSize, varName, tokens[numTokens], varValues, dictionary);
            numTokens++;
            break;
        }
        
        switch (tokens[numTokens].type) { // handle token based on token type
        case 0: // number
            processNumber(stack, tokens[numTokens]);
            numTokens++;
            break;
        case 1: // symbol
            processSymbol(stack, tokens[numTokens], &variableDecleration);
            numTokens++;
            break;
        case 2: // operator
            execute_stack_operation(stack, tokens[numTokens].text);
            numTokens++;
            break;
        case 3: // word
            processWord(stack, tokens[numTokens], dictionary);
            int isSuccesful = execute_stack_operation(stack, tokens[numTokens].text);
            if(isSuccesful == 0){// word not found
                
            }
            numTokens++;
            break;
        default: // default
            break;
    }
    }
}