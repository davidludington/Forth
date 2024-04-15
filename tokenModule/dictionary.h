#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "token.h"

struct dictionary_item {
    char *text; //the word that resembles the operations
    token_t *tokens;
};

struct dictionary {
    struct dictionary_item *items; // Array of dictionary items
    int size;                      // Size of the dictionary
};

struct dictionary create_dictionary();
void add_dictionary_item(struct dictionary dict, char *text, token_t *tokens);

token_t *get_dictionary_item(struct dictionary dict, char *text);


#endif