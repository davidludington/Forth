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

void processConditional(stack_i* stack, token_t token){
    //if (strcmp(token.text, "IF") == 0) if_statement(stack);
    //else if (strcmp(token.text, "ELSE") == 0) else_statement(stack);
    //else if (strcmp(token.text, "THEN") == 0) then_statement(stack);
}


void parseif(stack_i *stk, token_t* tokens, int current_position){
    int numTokens = current_position + 1;
    while (tokens[numTokens].text != NULL) {
        if (tokens[numTokens].type == CONDITIONAL) {
            parseif(stk, tokens, numTokens);
        }
        if (strcmp(tokens[numTokens].text, "ELSE") == 0) {
            while (strcmp(tokens[numTokens].text, "THEN") != 0) {
                numTokens++;
                if (tokens[numTokens].text == NULL) {
                    // Syntax error: Unexpected end of input
                    return;
                }
            }
        }
        if (strcmp(tokens[numTokens].text, "THEN") == 0) {
            return;
        }
        numTokens++;
    }
}
/*
void pasrseif(stack_i *stk){
    token_t token;
    stack_pop(stk, &token);
    if(token.type == CONDITIONAL){
        if(strcmp(token.text, "IF") == 0){
            token_t token2;
            token_t *tokenArray;
            stack_pop(stk, &token2);
            while(token2.type != CONDITIONAL){

                stack_pop(stk, &token2);
            }
            pasrseif(stk);
        }

    }
}
*/

void initiateLoop(int* starting_ending, int* isInLoop, stack_i* stack, int* tokenAmount){
    int top_value, next_to_top_value;
    stack_pop(stack, &top_value);
    stack_pop(stack, &next_to_top_value);
    //set the array of staring and ending
    starting_ending[0] = top_value;
    starting_ending[1] = next_to_top_value;
    
    //begin loop
    *isInLoop = 1;
    *tokenAmount = 0;

}

void pushTokenToLoop(token_t** loopTokens, int* tokenAmount, token_t newToken) {
    // Allocate memory for one more token
    *loopTokens = (token_t*)realloc(*loopTokens, (*tokenAmount + 1) * sizeof(token_t));

    // Copy the new token to the last position in the array
    (*loopTokens)[*tokenAmount] = newToken;

    // Increment the tokenAmount
    (*tokenAmount)++;
}

token_t* cleanUpI(const token_t* loopTokens, int tokenAmount, int currentIteration) {
    const char* targetText = "i";

    // Allocate memory for the new array of tokens
    token_t* newTokens = (token_t*)malloc(tokenAmount * sizeof(token_t));

    // Copy each token from the original array to the new array and modify as needed
    for (int i = 0; i < tokenAmount; i++) {
        // Allocate memory for the text field in the new token
        newTokens[i].text = (char*)malloc((strlen(loopTokens[i].text) + 1) * sizeof(char));
        strcpy(newTokens[i].text, loopTokens[i].text); // Copy the text field
        newTokens[i].type = loopTokens[i].type; // Copy the type field
        if (strcmp(loopTokens[i].text, targetText) == 0) {
            snprintf(newTokens[i].text, strlen(loopTokens[i].text) + 1, "%d", currentIteration);
            newTokens[i].type = NUMBER; // Assign NUMBER type to tokens where text matches "i"
        }
    }

    return newTokens;  // Return the new array
}


void runLoop(int* starting_ending, int* isInLoop, stack_i* stack, token_t* loopTokens, int tokenAmount, dictionary *dictionary){

    for(int i = starting_ending[0]; i < starting_ending[1]; i++){
        //the loop
        token_t* cleanedTokens = cleanUpI(loopTokens, tokenAmount, i);
        cleanedTokens[tokenAmount].text = NULL;
        process_to_stack(stack, cleanedTokens, dictionary);
        free(cleanedTokens);
    }
    *isInLoop = 0;
}




void process_to_stack(stack_i* stack, token_t* tokens, dictionary *dictionary){
    
    int numTokens = 0;
    
    int dictIsOpen = 0; // for dictionary use
    
    //for loop use
    int isInLoop = 0; 
    int starting_ending[2];
    token_t* loopTokens;
    int tokenAmount = 0;

    //cycle through tokens
    while (tokens[numTokens].text != NULL) {
        if(dictIsOpen == 1){ // this token is part of a var decletation
            push_dictionary(&dictIsOpen, dictionary, tokens[numTokens]);
            numTokens++;
            continue;
        }
        if(isInLoop == 1 && strcmp(tokens[numTokens].text, "loop") != 0){ // this token is part of a var decletation
            // push to the loopTokens
            pushTokenToLoop(&loopTokens, &tokenAmount, tokens[numTokens]);
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
            if(strcmp(tokens[numTokens].text, "do") == 0) initiateLoop(starting_ending, &isInLoop, stack, &tokenAmount); // start loop
            else if (strcmp(tokens[numTokens].text, "loop") == 0) runLoop(starting_ending, &isInLoop, stack, loopTokens, tokenAmount, dictionary);
            else processWord(stack, tokens[numTokens], dictionary);
            numTokens++;
            break;
        case COMPARISON: //comparison 
            processComparison(stack, tokens[numTokens]);
            numTokens++;
            break;
        case CONDITIONAL: //comparison 
            //processConditional(stack, tokens[numTokens]);
            numTokens++;
            break;
        default: // default
            break;
    }
    }
    numTokens = 0;
}