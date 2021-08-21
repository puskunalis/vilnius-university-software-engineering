#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "stack.h"

int getElementIndex(int* array, int size, int element)
{
    for (int i = 0; i < size; ++i)
    {
        if (array[i] == element)
        {
            return i;
        }
    }

    return -1;
}

double getArrayAverage(int* array, int size)
{
    int sum = 0;

    for (int i = 0; i < size; ++i)
    {
        sum += array[i];
    }

    return (double) sum / size;
}

int getArrayMax(int* array, int size)
{
    int maxElement = array[0];

    for (int i = 1; i < size; ++i)
    {
        if (array[i] > maxElement)
        {
            maxElement = array[i];
        }
    }

    return maxElement;
}

void runCafeteria(int plates, int timeToEat, int chanceToArrive, int timeToWash, int runningTime)
{
    Stack *dishwasher = createStack();

    int unservedClients = 0;

    int *platesInDishwasher = (int*) malloc(runningTime * sizeof(int));
    int *plateWashingEndTimes = (int*) calloc(runningTime, sizeof(int));

    for (int i = 0; i < runningTime; ++i)
    {
        // If a new client arrives
        if (rand() % 100 <= chanceToArrive)
        {
            if (plates > 0)
            {
                --plates;

                push(dishwasher, 0);
                plateWashingEndTimes[i] = i + timeToEat + timeToWash;
            }
            else
            {
                ++unservedClients;
            }
        }

        // Take cleaned plates out of the dishwasher
        int index;

        while (i != 0 && (index = getElementIndex(plateWashingEndTimes, runningTime, i)) != -1)
        {
            plateWashingEndTimes[index] = 0;
            pop(dishwasher);
            ++plates;
        }

        // Plates in the dishwasher at the current time moment
        platesInDishwasher[i] = getSize(dishwasher);
    }

    free(plateWashingEndTimes);

    printf("Number of clients who couldn't be served due to a lack of plates: %d\n", unservedClients);
    printf("Average plates in dishwasher at any time moment: %f\n", getArrayAverage(platesInDishwasher, runningTime));
    printf("Max number of plates in the dishwasher: %d\n", getArrayMax(platesInDishwasher, runningTime));

    free(platesInDishwasher);

    destroyStack(dishwasher);
}

int main()
{
    srand(time(0));

    int plates = 20;
    int timeToEat = 50;
    int chanceToArrive = 10;
    int timeToWash = 50;
    int runningTime = 10000;

    for (int i = 0; i < 10; ++i)
    {
        runCafeteria(plates, timeToEat, chanceToArrive, timeToWash, runningTime);
        printf("\n");
    }

    return 0;
}
