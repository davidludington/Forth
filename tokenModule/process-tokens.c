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
        } else{
            //if the token does not exist in the dictionary print the word with a question mark
            printf("%s ? \n", token.text);
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

token_t* advanceToCurrentToken(token_t* tokens, int* current_position){
    token_t* current_token = &tokens[*current_position];
    (*current_position)++;
    return current_token;
}


void parseif(stack_i *stk, token_t* tokens, int *current_position, dictionary *dict){
    //: is-it-zero?  0 = if ." Yes!" else ." No!" then ;
    //condition comes before if statement and pushes -1 or 0 onto stack 
    // : zero? 0 = if -1 else 0 then ;
    if(strcmp(tokens[*current_position].text, "then") == 0){ //base case 
        return;
    }
    int condition;
    printf("%s\n", tokens[*current_position].text);
    stack_print_console(stk);
    if(strcmp(tokens[*current_position].text, "if") == 0){ // need to make sure that the conditon is only applied for the first recursive call
        stack_pop(stk, &condition);
    }
    printf("%s\n", tokens[*current_position].text);
    
    

    if(condition == -1){ //condition is true 
        while (tokens[*current_position].text != NULL || strcmp(tokens[*current_position].text, "then") == 0){ //iterate over stack hel
            (*current_position)++;
            printf("%s\n", tokens[*current_position].text);
            if(tokens[*current_position].type != CONDITIONAL){
                process_to_stack(stk, advanceToCurrentToken(tokens, current_position), dict); //I think it is passing in all the tokens again from the parameter so it restarts the call from the begining of the statement 
                (*current_position)++;
            }else{
                parseif(stk, tokens, current_position, dict);
            }
            
        }
    } else if(condition == 0) { //condition is false ie 0, must iterate until "else" keyword then process to stack until we reach then
        while(strcmp(tokens[*current_position].text, "else") != 0 || strcmp(tokens[*current_position].text, "then") != 0){
            (*current_position)++;
            printf("%s\n", tokens[*current_position].text);
            if((strcmp(tokens[*current_position].text, "if") == 0) || (strcmp(tokens[*current_position].text, "else") == 0) || (strcmp(tokens[*current_position].text, "then") == 0)){
                parseif(stk, tokens, current_position, dict);
            }
        }

        while (tokens[*current_position].text != NULL || strcmp(tokens[*current_position].text, "then") == 0){
            process_to_stack(stk, advanceToCurrentToken(tokens, current_position), dict);
        }
    }
    
}

/*
void parseif(stack_i *stk, token_t* tokens, int *current_position, dictionary *dict){
    //: is-it-zero?  0 = if ." Yes!" else ." No!" then ;
    //condition comes before if statement and pushes -1 or 0 onto stack 
    // : zero? 0 = if -1 else 0 then ;
    int condition;
    printf("%s\n", tokens[*current_position].text);
    if(strcmp(tokens[*current_position].text, "if") == 0){ // need to make sure that the conditon is only applied for the first recursive call
        int num = stack_pop(stk, &condition);
        printf("%d", num);
    }
    if(strcmp(tokens[*current_position].text, "then") == 0){ //base case 
        return;
    }
    

    if(condition == -1){ //condition is true 
        while (tokens[*current_position].text != NULL || strcmp(tokens[*current_position].text, "then") == 0){ //iterate over stack hel
            (*current_position)++;
            if(tokens[*current_position].type != CONDITIONAL){
                process_to_stack(stk, tokens, dict);
                (*current_position)++;
            }else{
                parseif(stk, tokens, current_position, dict);
            }
            
        }
    } else if(condition == 0) { //condition is false ie 0, must iterate until "else" keyword then process to stack until we reach then
        while(strcmp(tokens[*current_position].text, "else") != 0 || strcmp(tokens[*current_position].text, "then") != 0){
            (*current_position)++;
            printf("%s\n", tokens[*current_position].text);
            if((strcmp(tokens[*current_position].text, "if") == 0) || (strcmp(tokens[*current_position].text, "else") == 0) || (strcmp(tokens[*current_position].text, "then") == 0)){
                parseif(stk, tokens, current_position, dict);
            }
        }

        while (tokens[*current_position].text != NULL || strcmp(tokens[*current_position].text, "then") == 0){
            process_to_stack(stk, tokens, dict);
        }
    }
    
}



/*
pop token off stack if it is -1 then process until you find another keyword(do, if, else)
if it is 0 skip over tokens until you find else and process until yuo get to then
/*
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
    */

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
        case CONDITIONAL: //Conditonal
            parseif(stack, tokens, &numTokens, dictionary);
            //if(strcmp(tokens[numTokens].text, "if") == 0) parseif(stack, tokens, &numTokens, dictionary);
            //if(strcmp(tokens[numTokens].text, "else") == 0) parseelse(stack, tokens, &numTokens, dictionary);
            numTokens++;
            break;
        default: // default
            break;
    }
    }
    numTokens = 0;
}