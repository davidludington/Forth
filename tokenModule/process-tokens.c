#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "token.h"
#include "dictionary.h"
#include "process-tokens.h"
#include <ctype.h>
#include <limits.h>



void processNumber(stack_i* stack, token_t* token) {

    char* endptr;
    long num_int = atoi(token->text); // THE ISSUE IS HERE
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
void processWord(stack_i* stack, token_t token, dictionary* dict){
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
        
        token_t *tokens = retrieve_dict_tokens(dict, token.text);
        if (tokens != NULL) {
            // Process the tokens if they are found
            process_to_stack(stack, tokens, dict);
        }
        //free(tokens);
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

void process_to_stack(stack_i* stack, token_t* tokens, dictionary *dictionary){
    int numTokens = 0;
    int dictIsOpen = 0;
    //cycle through tokens
    while (tokens[numTokens].text != NULL) {
        if(dictIsOpen == 1){ // this token is part of a var decletation
            push_dictionary(&dictIsOpen, dictionary, tokens[numTokens]);
            numTokens++;
            continue;
        }
        switch (tokens[numTokens].type) { // handle token based on token type

        case NUMBER: // number
            processNumber(stack, &tokens[numTokens]);
            numTokens++;
            break;
        case SYMBOL: // symbol
            push_dictionary(&dictIsOpen, dictionary, tokens[numTokens]);
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
        case CONDITIONAL: //comparison 
            processComparison(stack, tokens[numTokens]);
            numTokens++;
            break;
        default: // default
            break;
    }
    }
    numTokens = 0;
}