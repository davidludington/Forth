// int_stack.h - interface to the int_stack

#ifndef INT_STACK_H
#define INT_STACK_H

#include <stdio.h>
#include <sys/queue.h>

typedef struct int_entry {
    int value;
    SLIST_ENTRY(int_entry) entries;
} entry_t;

typedef struct stack {
    SLIST_HEAD(stackhead, int_entry) head;
    int size;
    int capacity;
} stack_i;

void stack_init(stack_i *stk, int capacity);
int stack_push(stack_i *stk, int value);
int stack_pop(stack_i *stk, int *top_value);
int stack_iop(stack_i *stk, int *top_value);
int stack_dup(stack_i *stk);
int stack_swap(stack_i *stk);
int stack_add(stack_i *stk);
int stack_sub(stack_i *stk);
int stack_mult(stack_i *stk);
int stack_div(stack_i *stk);
int stack_qmod(stack_i *stk);
int stack_mod(stack_i *stk);
int stack_swap(stack_i *stk);
int stack_dup(stack_i *stk);
int stack_over(stack_i *stk);
int stack_rot(stack_i *stk);
int stack_drop(stack_i *stk);
int two_dup(stack_i *stk);
int two_swap(stack_i *stk);
int two_over(stack_i *stk);
int two_drop(stack_i *stk);
void stack_print(stack_i *stk, FILE *file);
void stack_print_console(stack_i *stk);


#endif // INT_STACK_H