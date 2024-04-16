#ifndef PROCESS_TOKENS_H
#define PROCESS_TOKENS_H

#include "stack.h"
#include "token.h"
#include "dictionary.h" // Include the dictionary header file if needed

/* Function prototypes */

// void processNumber(stack_i* stack, token_t token);
// void processSymbol(stack_i* stack, token_t token, int* varDec);
// void processWord(stack_i* stack, token_t token, dictionary dict);
// void processOperator(stack_i* stack, token_t token);
void processComparison(stack_i* stack, token_t token);

void process_to_stack(stack_i* stack, token_t* tokens, dictionary* dictionary);

#endif /* PUSH_TOKENS_H */
