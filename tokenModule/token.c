#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

//add more if you see fit
const char *OPERATORS[] = {"+", "-", "*", "/"};
const char *SYMBOLS[] = {":", ";"};

// Function to create a token
struct token_t create_token(enum token_type_t type, const char *text) {
    struct token_t token;
    token.type = type;
    token.text = strdup(text);  // Duplicate the input text to avoid memory issues
    return token;
}

int isNotWhitespace(char c) {
    return c != ' ' && c != '\t' && c != '\n';
}

int isOperator(const char *input) {
    size_t numOperators = sizeof(OPERATORS) / sizeof(OPERATORS[0]);

    for (size_t i = 0; i < numOperators; ++i) {
        if (strcmp(input, OPERATORS[i]) == 0) {
            return 1; // Input is an operator
        }
    }
    return 0; // Input is not an operator
}

int isSymbol(const char *input) {
    size_t numSymbols = sizeof(SYMBOLS) / sizeof(SYMBOLS[0]);

    for (size_t i = 0; i < numSymbols; ++i) {
        if (strcmp(input, SYMBOLS[i]) == 0) {
            return 1; // Input is an operator
        }
    }
    return 0; // Input is not an operator
}

int isNumber(const char *str) {
    // Handle the case where the string is empty
    if (*str == '\0') {
        return 0;
    }

    // Check each character in the string
    while (*str != '\0') {
        if (!(*str >= '0' && *str <= '9')) {
            return 0; // If any character is not a digit, it's not a number
        }
        str++;
    }

    return 1; // All characters are digits, so it's a number
}


//converts the line of user input into an array of words
char **splitWords(char *userInput) {
    char **words = NULL;
    int wordsSize = 0;

    char currentWord[20] = "";

    for (int i = 0; i< strlen(userInput); i++) {
        if (isNotWhitespace(userInput[i])) {
            strncat(currentWord, &userInput[i], 1);
        } else {
            if (strlen(currentWord) > 0) {
                // Allocate memory for the new word
                words = realloc(words, (wordsSize + 1) * sizeof(char *));
                // Duplicate the current word and add it to the array
                words[wordsSize] = strdup(currentWord);
                wordsSize++;
                // Reset the current word buffer
                currentWord[0] = '\0';
            }
        }
    }

    // Handle the last word
    if (strlen(currentWord) > 0) {
        words = realloc(words, (wordsSize + 1) * sizeof(char *));
        words[wordsSize] = strdup(currentWord);
        wordsSize++;
    }

    // Add a NULL pointer to indicate the end of the array
    words = realloc(words, (wordsSize + 1) * sizeof(char *));
    words[wordsSize] = NULL;

    return words;
}

//asignes token an enum 
struct token_t charecterizeToken(char *token) {
    if(strlen(token) == 1 && isOperator(token)){
        //is a operator
        return create_token(OPERATOR, token);
    }else if(strlen(token) == 1 && isSymbol(token)){
        return create_token(SYMBOL, token);
    }else{
        // decipher if its a number or else it is a word
        if(isNumber(token)){
           return create_token(NUMBER, token);
        }else{
        // it is a word
            return create_token(WORD, token);
        }
        
    }
}

// takes string of user input and return array of tokens  
struct token_t *getTokens(char* userInput) {
    char** tokens = splitWords(userInput);
    int arraySize = 0;
    struct token_t *returnTokens = malloc(sizeof(struct token_t));

    for (int i = 0; tokens[i] != NULL; i++) {
        // charecterize the token
        struct token_t newToken = charecterizeToken(tokens[i]);
        returnTokens[arraySize] = newToken;
        arraySize++;
        returnTokens = realloc(returnTokens, (arraySize + 1) * sizeof(struct token_t));
    }

    // add termination token with type -1 after the last token
    struct token_t terminationToken = { -1, NULL };
    returnTokens = realloc(returnTokens, (arraySize + 1) * sizeof(struct token_t));
    returnTokens[arraySize] = terminationToken;

    return returnTokens;
}

//prints tokens to console
void printTokens(struct token_t *tokens){
     for (int i = 0; tokens[i].type != -1; i++) {
        printf("Token %d:\n", i);
        printf("  Type: %d\n", tokens[i].type);
        printf("  Text: %s\n", tokens[i].text);
    }
}
