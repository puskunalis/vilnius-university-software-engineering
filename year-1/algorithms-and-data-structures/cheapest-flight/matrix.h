#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "stack.h"

typedef struct Flight
{
    char *origin;
    char *destination;
    int64_t price;
} Flight;

typedef struct Matrix
{
    int64_t *arr;
    uint64_t numberOfCities;
    char **cities;
} Matrix;

Matrix* createMatrix(Flight flights[], size_t numberOfFlights);

void printMatrix(Matrix* matrix);
void printCities(Matrix* matrix);

int64_t findCheapestFlight(Matrix* matrix, char* origin, char* destination);

#endif // MATRIX_H
