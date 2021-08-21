// Vilius Puskunalis 5 grupe 17 uzduotis
#include <stdio.h>
#include <stdlib.h>
#include "doublyLinkedList.h"

node* createNode(int data)
{
    node *newNode = (node*) malloc(sizeof(node));

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void removeNode(struct node* node)
{
    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }
    else
    {
        node->next->prev = NULL;
    }

    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }
    else
    {
        node->prev->next = NULL;
    }

    free(node);
}

doublyLinkedList* createList()
{
    doublyLinkedList *list = (doublyLinkedList*) malloc(sizeof(doublyLinkedList));

    list->head = NULL;
    list->tail = NULL;

    return list;
}

void clearList(doublyLinkedList* list)
{
    if (list->head != NULL)
    {
        node *currentNode = list->head->next;

        while (currentNode != NULL)
        {
            free(currentNode->prev);
            currentNode = currentNode->next;
        }

        free(currentNode);
    }

    list->head = NULL;
    list->tail = NULL;
}

void push(doublyLinkedList* list, int data)
{
    if (list != NULL)
    {
        node *newNode = createNode(data);

        if (list->tail != NULL)
        {
            newNode->prev = list->tail;
            newNode->prev->next = newNode;
        }
        else
        {
            list->head = newNode;
        }

        list->tail = newNode;
    }
}

void unshift(doublyLinkedList* list, int data)
{
    if (list != NULL)
    {
        node *newNode = createNode(data);

        if (list->head != NULL)
        {
            newNode->next = list->head;
            newNode->next->prev = newNode;
        }
        else
        {
            list->tail = newNode;
        }

        list->head = newNode;
    }
}

void printElementsForward(doublyLinkedList* list)
{
    if (list != NULL && list->head != NULL)
    {
        node *currentNode = list->head;

        while (currentNode != NULL)
        {
            printf("%d ", currentNode->data);
            currentNode = currentNode->next;
        }

        printf("\n");
    }
}

void printElementsBackward(doublyLinkedList* list)
{
    if (list != NULL && list->tail != NULL)
    {
        node *currentNode = list->tail;

        while (currentNode != NULL)
        {
            printf("%d ", currentNode->data);
            currentNode = currentNode->prev;
        }

        printf("\n");
    }
}
