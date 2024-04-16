#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include "token.h"

dictionary *create_dictionary() {
    // Allocate memory for the dictionary pointer
    dictionary *dictPtr = malloc(sizeof(dictionary));
    if (dictPtr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize the dictionary members
    dictPtr->size = 0;
    dictPtr->nextIsWord = 0;
    dictPtr->items = malloc(0 * sizeof(dictionary_item)); // Allocate memory for items
    if (dictPtr->items == NULL) {
        printf("Memory allocation failed\n");
        free(dictPtr); // Free the previously allocated memory
        exit(1);
    }

    return dictPtr; // Return the pointer to the dictionary
}

token_t *get_dictionary_item(dictionary *dict, char *text) {
    // Iterate through the dictionary items to find the matching text
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].text, text) == 0) {
            // Return the tokens if the text matches
            return dict->items[i].tokens;
        }
    }
    // Return null if the text is not found in the dictionary
    return NULL;
}

void add_dictionary_instance(dictionary *dict, char *text) {
    // Reallocate memory for items
    dict->items = (dictionary_item*)realloc(dict->items, (dict->size + 1) * sizeof(dictionary_item));
    // Add the new item
    dict->items[dict->size].text = strdup(text); // Copy the text
    dict->size++;
}

void push_token_to_dict(dictionary *dict, token_t token) {
    printf("dictionary size %d\n", dict->items[dict->size - 1].size); // Use dict->size - 1 to access the last item
    if (dict->items[dict->size - 1].size == 0) {
        printf("size is null\n");
        dict->items[dict->size - 1].tokens = (token_t *)malloc(sizeof(token_t)); // Allocate memory for one token
        dict->items[dict->size - 1].tokens[0] = token;
        dict->items[dict->size - 1].size = 1; // Update size to 1
    } else {
        printf("size is not null\n");
        int currentSize = dict->items[dict->size - 1].size;
        dict->items[dict->size - 1].tokens = (token_t *)realloc(dict->items[dict->size - 1].tokens, (currentSize + 1) * sizeof(token_t));
        dict->items[dict->size - 1].tokens[currentSize] = token; // Use currentSize for indexing
        dict->items[dict->size - 1].size++; // Increment size after adding a token
    }
}





void push_dictionary(int *isDictionaryOpen, dictionary *dictionary, token_t token){
    if(strcmp(token.text, ";") == 0){
        printf("closing dict\n");
        isDictionaryOpen = 0; // close the dictionary
    } else if (strcmp(token.text, ":") == 0) {
        printf("openning dict\n");
        // the next token is the word
        *isDictionaryOpen = 1; // open dictionary
        // the line below this doesnt work, why?
        dictionary->nextIsWord = 1; // expect next token to be word 
    }else if(dictionary->nextIsWord){
        printf("the word\n");
        // adds new word to dictionary
        dictionary->nextIsWord = 0;
        add_dictionary_instance(dictionary, token.text);
    }else{
        printf("a token\n");
        // add token to recent entry
        push_token_to_dict(dictionary, token);
    }
}


void print_dictionary_words(dictionary *dict) {
    if (dict == NULL || dict->items == NULL) {
        printf("Dictionary is empty or invalid.\n");
        return;
    }

    printf("Words in the dictionary:\n");

    for (int i = 0; i < dict->size; i++) {
        dictionary_item item = dict->items[i];
        if (item.tokens != NULL && item.size > 0) {
            printf("%s\n", item.text); // Print the word associated with the dictionary item
        }
    }
}