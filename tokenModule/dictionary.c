#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include "token.h"

dictionary create_dictionary() {
    // Allocate memory for the dictionary
    dictionary dict;
    dict.size = 0; // Start with size 0
    dict.items = malloc(0 * sizeof(dictionary_item)); // Allocate memory for items
    
    return dict;
}

void add_dictionary_item(struct dictionary dict, char *text, token_t *tokens) {
    // Reallocate memory for items
    dict.items = (struct dictionary_item*)realloc(dict.items, (dict.size + 1) * sizeof(dictionary_item));
    // Add the new item
    dict.items[dict.size].text = strdup(text); // Copy the text
    dict.items[dict.size].tokens = tokens;
    dict.size++;
}

token_t *get_dictionary_item(struct dictionary dict, char *text) {
    // Iterate through the dictionary items to find the matching text
    for (int i = 0; i < dict.size; i++) {
        if (strcmp(dict.items[i].text, text) == 0) {
            // Return the tokens if the text matches
            return dict.items[i].tokens;
        }
    }
    // Return null if the text is not found in the dictionary
    return NULL;
}