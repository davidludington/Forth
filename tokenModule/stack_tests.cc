/* test cases */

#include <gtest/gtest.h>

extern "C" {
#include "stack.h"
#include "process-tokens.h"
#include "token.h"
#include "dictionary.h"
}

TEST(StackTest, Initialization)
{
    stack_i stack_test;
    stack_init(&stack_test, 8);
    stack_push(&stack_test, 1);
    stack_push(&stack_test, 2);
    stack_push(&stack_test, 3);
    stack_push(&stack_test, 4);
    ASSERT_EQ(stack_test.size, 4);
    ASSERT_EQ(stack_test.capacity, 8);
}

TEST(StackTest, Capacity)
{
    stack_i stack;
    stack_init(&stack, 2);
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    ASSERT_EQ(stack_push(&stack, 3), 0);
}
TEST(StackTest, SimpleOperations)
{
    stack_i stack;
    stack_init(&stack, 2);
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_add(&stack);
    //addition
    int add_result;
    stack_pop(&stack, &add_result);
    ASSERT_EQ(add_result, 3);
    //subtraction
    stack_push(&stack, 3);
    stack_push(&stack, 5);
    int sub_result;
    stack_sub(&stack);
    stack_pop(&stack, &sub_result);
    ASSERT_EQ(sub_result, -2);
    //divide
    stack_push(&stack, 4);
    stack_push(&stack, 2);
    int div_result;
    stack_div(&stack);
    stack_pop(&stack, &div_result);
    ASSERT_EQ(div_result, 2);
    //mult
    stack_push(&stack, 2);
    stack_push(&stack, 2);
    int mult_result;
    stack_mult(&stack);
    stack_pop(&stack, &mult_result);
    ASSERT_EQ(mult_result, 4);
    //qmod
    stack_push(&stack, 2);
    stack_push(&stack, 5);
    int division, remainder;
    stack_qmod(&stack);
    stack_pop(&stack, &division);
    stack_pop(&stack, &remainder);
    ASSERT_EQ(division, 2);
    ASSERT_EQ(remainder, 1);
    stack_print_console(&stack);
    //mod
    stack_push(&stack, 2);
    stack_push(&stack, 5);
    int mod_result;
    stack_mod(&stack);
    stack_pop(&stack, &mod_result);
    ASSERT_EQ(mod_result, 1);
}
TEST(StackTest, StackManipulaiton)
{
    stack_i stack;
    stack_init(&stack, 5);
    int first_value, second_value, thrid_value;
    //swap
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_swap(&stack);
    
    stack_pop(&stack, &first_value);
    stack_pop(&stack, &second_value);
    ASSERT_EQ(first_value, 1);
    ASSERT_EQ(second_value, 2);
    // over
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_over(&stack);
    stack_pop(&stack, &first_value);
    ASSERT_EQ(first_value, 1);
    // rotate
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_push(&stack, 3);
    stack_rot(&stack);
    stack_pop(&stack, &first_value);
    ASSERT_EQ(first_value, 1);
    // stack drop
    stack_drop(&stack);
    stack_pop(&stack, &first_value);
    ASSERT_EQ(first_value, 2);
}
TEST(StackTest, PairOperations)
{
    stack_i stack;
    stack_init(&stack, 8);
    int first_value, second_value, thrid_value, fourth_value;
    // two swap
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_push(&stack, 3);
    stack_push(&stack, 4);
    two_swap(&stack);
    stack_pop(&stack, &first_value);
    stack_pop(&stack, &second_value);
    ASSERT_EQ(first_value, 2);
    ASSERT_EQ(second_value, 1);
    // two dup
    two_dup(&stack);
    stack_pop(&stack, &first_value);
    stack_pop(&stack, &second_value);
    ASSERT_EQ(first_value, 4);
    ASSERT_EQ(second_value, 3);
    // two over 
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    two_over(&stack);
    stack_pop(&stack, &first_value);
    stack_pop(&stack, &second_value);
    ASSERT_EQ(first_value, 4);
    ASSERT_EQ(second_value, 3);
    // two drop
    two_drop(&stack);
    stack_pop(&stack, &first_value);
    stack_pop(&stack, &second_value);
    ASSERT_EQ(first_value, 4);
    ASSERT_EQ(second_value, 3);
}

TEST(Tokens, TokenProcessing){
    const char* input = "1 2 3 +"; // Use const char* instead of char*
    stack_i stack;
    stack_init(&stack, 8);
    dictionary *dictionary = create_dictionary();
    // apparently I need to do this for c compatibility
    token_t* tokens = getTokens(const_cast<char*>(input));
    process_to_stack(&stack, tokens, dictionary); 
    entry_t* entry;
    int pos = 0; 
    SLIST_FOREACH(entry, &stack.head, entries) {
        if(pos == 0){
            ASSERT_EQ(entry->value, 5); // 3 + 2
        }else{
            ASSERT_EQ(entry->value, 1); // other value on stack
        }
        pos++; // Increment pos
    }
  
    free(tokens);
}


TEST(Tokens, Dictionary){
    const char* input = "100"; // Use const char* instead of char*
    stack_i stack;
    stack_init(&stack, 8);
    dictionary *dictionary = create_dictionary();
    // apparently I need to do this for c compatibility
    token_t* tokens = getTokens(const_cast<char*>(input));
    process_to_stack(&stack, tokens, dictionary); 

    const char* secondInput = ": foo 100 + ;";
    token_t* secondTokens = getTokens(const_cast<char*>(secondInput));
    process_to_stack(&stack, secondTokens, dictionary); 
    
    const char* thirdInput = "foo";
    token_t* thirdTokens = getTokens(const_cast<char*>(thirdInput));
    process_to_stack(&stack, thirdTokens, dictionary); 


    entry_t* entry;
    int pos = 0; 
    SLIST_FOREACH(entry, &stack.head, entries) {
        if(pos == 0){
            ASSERT_EQ(entry->value, 200); // 100 + 100
        }
        pos++; // Increment pos
    }
    free(tokens);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}