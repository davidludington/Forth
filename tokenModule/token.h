#ifndef TOKEN_H
#define TOKEN_H
// Enum to represent token types
enum token_type_t {
    NUMBER,
    SYMBOL,
    OPERATOR,
    WORD
};
// Struct to represent a token
struct token_t {
    enum token_type_t type;
    char *text;
};


extern struct token_t *getTokens(char* userInput);

extern void printTokens(struct token_t *tokens);

#endif