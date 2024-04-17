#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "token.h"

typedef struct{
    char *text; //the word that resembles the operations
    token_t *tokens;
    int size;
}dictionary_item;

typedef struct  {
    dictionary_item *items; // Array of dictionary items
    int nextIsWord; // bool for if the next token is a word
    int size; // Size of the dictionary
}dictionary;

dictionary *create_dictionary();
void add_dictionary_item(dictionary dict, char *text, token_t *tokens);

void push_dictionary(int *isDictionaryOpen, dictionary *dictionary, token_t token);
token_t* retrieve_dict_tokens(dictionary *dict, char *word);
void print_dictionary_words(dictionary *dict);


#endif