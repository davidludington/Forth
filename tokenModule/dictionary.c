#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include "token.h"

dictionary *create_dictionary() {
    dictionary *dictPtr = malloc(sizeof(dictionary));
    if (dictPtr == NULL) {
        return NULL; // Allocation failed
    }

    dictPtr->size = 0;
    dictPtr->nextIsWord = 0;
    dictPtr->items = malloc(0 * sizeof(dictionary_item));
    if (dictPtr->items == NULL) {
        free(dictPtr);
        return NULL; // Allocation failed
    }

    return dictPtr;
}

void push_token_to_dict(dictionary *dict, token_t token) {
dictionary_item *item = &dict->items[dict->size - 1]; 
if (item->size == 0) {
    // Allocate memory for one token if tokens array is empty
    item->tokens = (token_t *)malloc(sizeof(token_t));
    if (item->tokens == NULL) {
        // Memory allocation failed, handle error
        fprintf(stderr, "Error: Failed to allocate memory for tokens\n");
        return;
    }
    item->tokens[0] = token;
    item->size = 1; // Update size to 1
} else {
    // Reallocate memory for tokens array to add one more token
    int currentSize = item->size;
    item->tokens = (token_t *)realloc(item->tokens, (currentSize + 1) * sizeof(token_t));
    if (item->tokens == NULL) {
        // Memory reallocation failed, handle error
        fprintf(stderr, "Error: Failed to reallocate memory for tokens\n");
        return;
    }
    item->tokens[currentSize] = token; // Use currentSize for indexing
    item->size++; // Increment size after adding a token
}
}


void print_dictionary_words(dictionary *dict) {
    if (dict == NULL || dict->items == NULL) {
        return;
    }

    for (int i = 0; i < dict->size; i++) {
        dictionary_item *item = &dict->items[i];
        if (item != NULL && item->tokens != NULL && item->size > 0) {
            printf("%s\n", item->text); // Print the word associated with the dictionary item
        }
    }
}

token_t* retrieve_dict_tokens(dictionary *dict, char *word) {
    if (dict == NULL || dict->items == NULL || word == NULL) {
        return NULL; // Invalid dictionary or word
    }
    
    for (int i = 0; i < dict->size; i++) {
        dictionary_item *item = &dict->items[i]; // Use pointer to avoid copying
        if (item != NULL && item->tokens != NULL && item->size > 0 && strcmp(item->text, word) == 0) {
            return item->tokens; // Return the tokens associated with the word
        }
    }
    return NULL; // Word not found
}

void add_dictionary_instance(dictionary *dict, char *text) {
    // Reallocate memory for items
    dict->items = (dictionary_item*)realloc(dict->items, (dict->size + 1) * sizeof(dictionary_item));
    // Add the new item
    dict->items[dict->size].text = strdup(text); // Copy the text
    dict->size++;
}


void push_dictionary(int *isDictionaryOpen, dictionary *dictionary, token_t token){
    if(strcmp(token.text, ";") == 0){
        *isDictionaryOpen = 0; // close the dictionary
    } else if (strcmp(token.text, ":") == 0) {
        // the next token is the word
        *isDictionaryOpen = 1; // open dictionary
        // the line below this doesnt work, why?
        dictionary->nextIsWord = 1; // expect next token to be word 
    }else if(dictionary->nextIsWord){
        // adds new word to dictionary
        dictionary->nextIsWord = 0;
        add_dictionary_instance(dictionary, token.text);
    }else{
        // add token to recent entry
        push_token_to_dict(dictionary, token);
    }
}
