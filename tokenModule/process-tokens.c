#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "token.h"
#include "dictionary.h"
#include "process-tokens.h"


// add number to stack
void processNumber(stack_i* stack, token_t token){
    int num_int = atoi(token.text);
    // just push number to stack
    stack_push(stack, num_int);
}

// symbols help add variables
void processSymbol(stack_i* stack, token_t token, int* varDec){
    if (strcmp(token.text, ":") == 0) {
        // initilize valiable decleration
        *varDec = 1;
    }
}

// processing words
void processWord(stack_i* stack, token_t token, dictionary dict){
    if (strcmp(token.text, "dup") == 0) stack_dup(stack);
    else if (strcmp(token.text, "drop") == 0) stack_drop(stack);
    else if (strcmp(token.text, "swap") == 0) stack_swap(stack);
    else if (strcmp(token.text, "over") == 0) stack_over(stack);
    else if (strcmp(token.text, "rot") == 0) stack_rot(stack);
    else if (strcmp(token.text, "2drop") == 0) two_drop(stack);
    else if (strcmp(token.text, "2swap") == 0) two_swap(stack);
    else if (strcmp(token.text, "2over") == 0) two_over(stack);
    else if (strcmp(token.text, "2dup") == 0) two_dup(stack);
    // if none of these are true then check the dictionary
    else {
        //if it is in the dictionary
        token_t *tokens = get_dictionary_item(dict, token.text);
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
// manipulating stack based on operator
void processOperator(stack_i* stack, token_t token) {
    if (strcmp(token.text, "+") == 0) stack_add(stack);
    else if (strcmp(token.text, "-") == 0) stack_sub(stack);
    else if (strcmp(token.text, "*") == 0) stack_mult(stack);
    else if (strcmp(token.text, "/") == 0) stack_div(stack);
    else if (strcmp(token.text, ".") == 0) stack_drop(stack);
}

void processComparison(stack_i* stack, token_t token){
    if (strcmp(token.text, "=") == 0) equal(stack);
    else if (strcmp(token.text, "<>") == 0) not_equal(stack);
    else if (strcmp(token.text, "<") == 0) less_than(stack);
    else if (strcmp(token.text, ">") == 0) greater_than(stack);
    else if (strcmp(token.text, "<=") == 0) less_that_equal_to(stack);
    else if (strcmp(token.text, ">=") == 0) greater_that_equal_to(stack);
    else if (strcmp(token.text, "0<") == 0) zero_less_than(stack);
    else if (strcmp(token.text, "0>") == 0) zero_greater_than(stack);
}

void pushValesToVar(token_t* varValues, token_t token, int* varSize){
    varValues[*varSize] = token; // Dereference varSize to get the integer value
    *varSize = *varSize + 1; // Increment the size after adding the token
    varValues = realloc(varValues, (*varSize) * sizeof(token_t)); // Update the reallocated size
}

void handleVariableDecleration(int* variableDecleration, int* varSize, char* varName, token_t token, 
token_t* varValues, dictionary dict){
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


void process_to_stack(stack_i* stack, token_t* tokens, dictionary dictionary){
    
    int numTokens = 0;

    // for variable decleration
    int variableDecleration = 0;
    int varSize = 0;
    char* varName;

    token_t* varValues = malloc(sizeof(token_t));


    //cycle through tokens
    while (tokens[numTokens].text != NULL) {

        
        if(variableDecleration == 1){ // this token is part of a var decletation
            handleVariableDecleration(&variableDecleration, &varSize, varName, tokens[numTokens], varValues, dictionary);
            numTokens++;
            break;
        }
        
        switch (tokens[numTokens].type) { // handle token based on token type
        case NUMBER: // number
            processNumber(stack, tokens[numTokens]);
            numTokens++;
            break;
        case SYMBOL: // symbol
            processSymbol(stack, tokens[numTokens], &variableDecleration);
            numTokens++;
            break;
        case OPERATOR: // operator
            processOperator(stack, tokens[numTokens]);
            numTokens++;
            break;
        case WORD: // word
            processWord(stack, tokens[numTokens], dictionary);
            numTokens++;
            break;
        case COMPARISON: //comparison 
            processComparison(stack, tokens[numTokens]);
            numTokens++;
            break;
        default: // default
            break;
    }
    }
}