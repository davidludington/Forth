#ifndef TOKEN_H
#define TOKEN_H
// Enum to represent token types
typedef enum {
    NUMBER,
    SYMBOL,
    OPERATOR,
    WORD, 
    COMPARISON
}token_type_t;
// Struct to represent a token
typedef struct{
    token_type_t type;
    char *text;
}token_t;

static struct {
    char *word;
    token_type_t type;
} tokens[] = {
    {"+", OPERATOR},
    {"-", OPERATOR},
    {"*", OPERATOR},
    {"/", OPERATOR},
    {".", OPERATOR},
    {":", SYMBOL},
    {";", SYMBOL},
    {"<", COMPARISON},
    {"<=", COMPARISON},
    {"<>", COMPARISON},
    {">", COMPARISON},
    {">=", COMPARISON},
    {"=", COMPARISON},
    {"0<", COMPARISON},
    {"0>", COMPARISON},
    {NULL, SYMBOL} // add more here
};


extern token_t *getTokens(char* userInput);
extern token_t charecterizeToken(char *token);
extern char **splitWords(char *userInput);
extern token_t characterizeToken(char *token);
extern token_t* getTokens(char* userInput);
extern void printTokens(token_t *tokens);

#endif