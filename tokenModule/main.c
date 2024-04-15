#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "stack.h"
#include "dictionary.h"
#include "process-tokens.h"

//this is where the program starts

#define MAX_INPUT_SIZE 20

// Function to get a line of input
char* getInput() {
    char input[MAX_INPUT_SIZE]; // allocate memory here
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    char *usersInput = strdup(input);
    return usersInput;
}

int main(){

    stack_i* stack = malloc(sizeof(stack_i));
    stack_init(stack, 8);
    struct dictionary dictionary = create_dictionary();
    while(1){
        char* input = getInput();
        if (strcmp(input, "BYE") == 0){ // bye to exit
            free(input);
            break;
        }else{

            // divides input into tokens
            token_t* tokens = getTokens(input);
            // manipulates stack based on order of tokens
            process_to_stack(stack, tokens, dictionary);
            // prints out stack after computation
            stack_print_console(stack);
            free(tokens);
        }
    }
    free(stack);
}


