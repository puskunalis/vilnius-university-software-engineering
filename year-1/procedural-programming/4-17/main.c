// Vilius Puskunalis 5 grupe 17 uzduotis
#include <stdio.h>
#include <stdlib.h>
#include "doublyLinkedList.h"

void removeConsecutiveElements(doublyLinkedList* list)
{
    node *currentNode = list->head;

    while (currentNode != NULL && currentNode->next != NULL)
    {
        if (currentNode->data == currentNode->next->data)
        {
            removeNode(currentNode->next);
        }
        else
        {
            currentNode = currentNode->next;
        }
    }

    list->tail = currentNode;
}

int main()
{
    int data, position;
    doublyLinkedList *list = createList();

    printf("Enter a series of numbers in format \"[number] [insertion position 0/1]\" separated by spaces, ending it with \"0 0\":\n");
    scanf("%d %d", &data, &position);

    while (data != 0)
    {
        if (position == 1)
        {
            push(list, data);
        }
        else if (position == 0)
        {
            unshift(list, data);
        }

        scanf("%d %d", &data, &position);
    }

    printf("\nEntered series:\n");
    printElementsForward(list);

    removeConsecutiveElements(list);

    printf("\nThe series with consecutive elements removed, forward:\n");
    printElementsForward(list);

    printf("\nThe series with consecutive elements removed, backward:\n");
    printElementsBackward(list);

    clearList(list);
    free(list);

    return 0;
}
