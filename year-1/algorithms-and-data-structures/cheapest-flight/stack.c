#include "stack.h"

Stack* createStack()
{
    Stack *stack = (Stack*) malloc(sizeof(Stack));

    if (stack != NULL)
    {
        stack->size = 0;
        stack->top = NULL;
    }
    else
    {
        printf("Error: cannot create stack - out of memory!\n");
    }

    return stack;
}

void destroyStack(Stack *stack)
{
    if (stack != NULL)
    {
        while (stack->size > 0)
        {
            pop(stack);
        }

        free(stack);
    }
}

uint64_t getSize(Stack *stack)
{
    if (stack != NULL)
    {
        return stack->size;
    }
    else
    {
        printf("Error: null pointer! Returning -1.\n");
        return -1;
    }
}

Data peek(Stack *stack)
{
    if (stack != NULL)
    {
        if (stack->size > 0)
        {
            return stack->top->data;
        }
        else
        {
            printf("Error: stack is empty! Returning -1.\n");
            return -1;
        }
    }
    else
    {
        printf("Error: null pointer! Returning -1.\n");
        return -1;
    }
}

void push(Stack *stack, Data data)
{
    if (stack != NULL)
    {
        Node *node = (Node*) malloc(sizeof(Node));

        if (node != NULL)
        {
            node->data = data;
            node->lowerNode = stack->top;

            stack->size += 1;
            stack->top = node;
        }
        else
        {
            printf("Error: cannot push to stack - out of memory!\n");
        }
    }
    else
    {
        printf("Error: null pointer!\n");
    }
}

Data pop(Stack *stack)
{
    if (stack != NULL)
    {
        if (stack->size > 0)
        {
            Node *node = stack->top;
            Data data = node->data;
            stack->top = node->lowerNode;

            free(node);

            stack->size -= 1;

            return data;
        }
        else
        {
            printf("Error: attempted stack underflow! Returning -1. Stack size unchanged.\n");
            return -1;
        }
    }
    else
    {
        printf("Error: null pointer! Returning -1.\n");
        return -1;
    }
}
