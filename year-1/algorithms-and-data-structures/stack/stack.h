#ifndef STACK_H
#define STACK_H

#include <stdint.h>

typedef int64_t Data;

typedef struct Node
{
    Data data;
    struct Node *lowerNode;
} Node;

typedef struct Stack
{
    uint64_t size;
    struct Node *top;
} Stack;

Stack* createStack();
void destroyStack(Stack *stack);

uint64_t getSize(Stack *stack);
Data peek(Stack *stack);
void push(Stack *stack, Data data);
Data pop(Stack *stack);

#endif
