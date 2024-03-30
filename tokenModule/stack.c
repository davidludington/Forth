#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


void stack_init(stack_i *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

int stack_push(stack_i *stk, int value) {
    if (stk->size >= stk->capacity) {
        printf("Stack is at full capacity.\n");
        return 0; // fail
    }

    entry_t *newEntry = malloc(sizeof(entry_t));
    if (newEntry) {
        newEntry->value = value;
        SLIST_INSERT_HEAD(&stk->head, newEntry, entries);
        stk->size++;
        return 1; //success
    }
    return 0; // fail
}

int stack_pop(stack_i *stk, int *top_value) {
    entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stk->head, entries);
        free(entry);
        stk->size--;
        *top_value = value;
        return 1; // success
    }
    return 0; // fail
}

int stack_iop(stack_i *stk, int *top_value) {
    entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        *top_value = entry->value;
        return 1; // success
    }
    return 0; // fail
}

/* Functiosn for FORTH langauge stack operators */

int stack_dup(stack_i *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    stack_iop(stk, &top_value);
    return stack_push(stk, top_value); // success only if last operation succeeds
}

int stack_swap(stack_i *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    stack_push(stk, top_value);
    return stack_push(stk, next_to_top_value); // success only if last operation succeeds
}

/* Example of how to create a binary operator that works o top two elements (if present) */

int stack_add(stack_i *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    return stack_push(stk, top_value + next_to_top_value);
}
int stack_sub(stack_i *stk){
        if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    return stack_push(stk, top_value - next_to_top_value);
}
int stack_mult(stack_i *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    return stack_push(stk, top_value * next_to_top_value);
}
int stack_div(stack_i *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    return stack_push(stk, next_to_top_value / top_value);
}

int stack_qmod(stack_i *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    stack_push(stk, top_value % next_to_top_value);
    return stack_push(stk, top_value / next_to_top_value);
}
int stack_mod(stack_i *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    return stack_push(stk, top_value % next_to_top_value);
}
int stack_over(stack_i *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    stack_push(stk, next_to_top_value);
    stack_push(stk, top_value);
    return stack_push(stk, next_to_top_value);
}
int stack_rot(stack_i *stk){
    if (stk->size < 3)
        return 0;
    int top_value, next_to_top_value, third_value;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    stack_pop(stk, &third_value);
    stack_push(stk, next_to_top_value);
    stack_push(stk, top_value);
    return stack_push(stk, third_value);
}

int stack_drop(stack_i *stk){
    if (stk->size < 1)
        return 0;
    int top_value;
    return stack_pop(stk, &top_value);
}
int two_swap(stack_i *stk){
    if (stk->size < 4)
        return 0;
    int top_value, next_to_top_value, third, fourth;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    stack_pop(stk, &third);
    stack_pop(stk, &fourth);
    stack_push(stk, next_to_top_value);
    stack_push(stk, top_value);
    stack_push(stk, fourth);
    return stack_push(stk, third);
}
int two_dup(stack_i *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second;
    stack_pop(stk, &top_value);
    stack_pop(stk, &second);
    stack_push(stk, second);
    stack_push(stk, top_value);
    stack_push(stk, second);
    return stack_push(stk, top_value);
}
int two_over(stack_i *stk){
    if (stk->size < 4)
        return 0;
    int top_value, next_to_top_value, third, fourth;
    stack_pop(stk, &top_value);
    stack_pop(stk, &next_to_top_value);
    stack_pop(stk, &third);
    stack_pop(stk, &fourth);
    stack_push(stk, fourth);
    stack_push(stk, third);
    stack_push(stk, next_to_top_value);
    stack_push(stk, top_value);
    stack_push(stk, fourth);
    return stack_push(stk, third);
}
int two_drop(stack_i *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    stack_pop(stk, &top_value);
    return stack_pop(stk, &next_to_top_value);
}


int less_than(stack_i *stk){
    int top, next_to_top;
    stack_pop(stk, &top);
    stack_pop(stk, &next_to_top);
    if(next_to_top < top){
        stack_push(stk, 1);
        return 1; //return 1 if true, should we return -1 instead?
    }else{
        stack_push(stk, 0);
        return 0;
    }
}
int greater_than(stack_i *stk){
    int top, next_to_top;
    stack_pop(stk, &top);
    stack_pop(stk, &next_to_top);
    if(next_to_top > top){
        stack_push(stk, 1);
        return 1;
    }else{
        stack_push(stk, 0);
        return 0;
    }
}
int equal(stack_i *stk){
    int top, next_to_top;
    stack_pop(stk, &top);
    stack_pop(stk, &next_to_top);
    if(next_to_top == top){
        stack_push(stk, 1);
        return 1;
    }else{
        stack_push(stk, 0);
        return 0;
    }

}
int not_equal(stack_i *stk){
    int top, next_to_top;
    stack_pop(stk, &top);
    stack_pop(stk, &next_to_top);
    if(next_to_top != top){
        stack_push(stk, 1);
        return 1;
    }else{
        stack_push(stk, 0);
        return 0;
    }

}
int zero_less_than(stack_i *stk){
    int top;
    stack_pop(stk, &top);
    if(top < 0){
        stack_push(stk, 1);
        return 1;
    }else{
        stack_push(stk, 0);
        return 0;
    }

}
int zero_greater_than(stack_i *stk){
    int top;
    stack_pop(stk, &top);
    if(top > 0){
        stack_push(stk, 1);
        return 1;
    }else{
        stack_push(stk, 0);
        return 0;
    }
}
int zero_equal(stack_i *stk){
    int top;
        stack_pop(stk, &top);
    if(top == 0){
        stack_push(stk, 1);
        return 1;
    }else{
        stack_push(stk, 0);
        return 0;
    }
}



void stack_print(stack_i *stk, FILE *file) {
    entry_t *entry;
    int pos = 0;
    if (stk->size == 0) {
        fprintf(file, "empty stack\n");
    }
    SLIST_FOREACH(entry, &stk->head, entries) {
        fprintf(file, "%d: %d\n", pos, entry->value);
        pos++;
    }
}


void stack_print_console(stack_i *stk) {
    entry_t *entry;
    int values[stk->size]; // Assuming fixed-size arrays are acceptable

    // Store stack elements in an array
    int i = 0;
    SLIST_FOREACH(entry, &stk->head, entries) {
        values[i++] = entry->value;
    }

    // Print stack elements in reverse order
    for (i = stk->size - 1; i >= 0; i--) {
        printf("%d ", values[i]);
    }
    printf("<- Top\n");
}