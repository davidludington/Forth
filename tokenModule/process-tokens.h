#ifndef PROCESS_TOKENS_H
#define PROCESS_TOKENS_H

#include "stack.h"
#include "token.h"
#include "dictionary.h" // Include the dictionary header file if needed

/* Function prototypes */
void processNumber(stack_i* stack, struct token_t token);
void processSymbol(stack_i* stack, struct token_t token, int* varDec);
void processWord(stack_i* stack, struct token_t token, struct dictionary dict);
void processOperator(stack_i* stack, struct token_t token);
void pushValesToVar(struct token_t* varValues, struct token_t token, int* varSize);
void handleVariableDecleration(int* variableDecleration, int* varSize, char* varName, struct token_t token, 
                               struct token_t* varValues, struct dictionary dict);
void process_to_stack(stack_i* stack, struct token_t* tokens, struct dictionary dictionary);

#endif /* PUSH_TOKENS_H */
