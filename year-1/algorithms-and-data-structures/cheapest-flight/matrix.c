#include "matrix.h"

void addFlight(Matrix* matrix, Flight flight)
{
    size_t originCityIndex = -1, destinationCityIndex = -1;

    for (size_t i = 0; i < matrix->numberOfCities && (originCityIndex == -1 || destinationCityIndex == -1); i++)
    {
        if (strcmp(matrix->cities[i], flight.origin) == 0)
        {
            originCityIndex = i;
        }
        else if (strcmp(matrix->cities[i], flight.destination) == 0)
        {
            destinationCityIndex = i;
        }
    }

    *(matrix->arr + matrix->numberOfCities * originCityIndex + destinationCityIndex) = flight.price;
}

void addFlights(Matrix* matrix, Flight flights[], size_t numberOfFlights)
{
    for (size_t i = 0; i < numberOfFlights; i++)
    {
        addFlight(matrix, flights[i]);
    }
}

void initializeMatrix(Matrix* matrix)
{
    matrix->arr = (int64_t*) malloc(matrix->numberOfCities * matrix->numberOfCities * sizeof(int64_t));

    for (size_t i = 0; i < matrix->numberOfCities * matrix->numberOfCities; i++)
    {
        *(matrix->arr + i) = -1;
    }
}

void addCity(Matrix* matrix, char* city)
{
    char cityFound = 0;

    for (size_t i = 0; i < matrix->numberOfCities; i++)
    {
        if (strcmp(*(matrix->cities + i), city) == 0)
        {
            cityFound = 1;
            break;
        }
    }

    if (!cityFound)
    {
        matrix->cities = realloc(matrix->cities, (matrix->numberOfCities + 1) * sizeof(char*));
        matrix->cities[matrix->numberOfCities] = city;
        matrix->numberOfCities++;
    }
}

void addCities(Matrix* matrix, Flight flights[], size_t numberOfFlights)
{
    for (size_t i = 0; i < numberOfFlights; i++)
    {
        addCity(matrix, flights[i].origin);
        addCity(matrix, flights[i].destination);
    }
}

Matrix* createMatrix(Flight flights[], size_t numberOfFlights)
{
    Matrix *matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->cities = (char**) malloc(0);
    matrix->numberOfCities = 0;

    addCities(matrix, flights, numberOfFlights);
    initializeMatrix(matrix);
    addFlights(matrix, flights, numberOfFlights);

    return matrix;
}

void printMatrix(Matrix* matrix)
{
    for (size_t i = 0; i < matrix->numberOfCities; i++)
    {
        for (size_t j = 0; j < matrix->numberOfCities; j++)
        {
            printf("%d ", *(matrix->arr + i*matrix->numberOfCities + j));
        }
        printf("\n");
    }
}

void printCities(Matrix* matrix)
{
    for (size_t i = 0; i < matrix->numberOfCities; i++)
    {
        printf("%d: %s\n", i, matrix->cities[i]);
    }
}

bool isCityVisited(size_t* visitedCities, size_t* visitedCitiesNumber, size_t nextCity)
{
    for (size_t i = 0; i < *visitedCitiesNumber; i++)
    {
        if (visitedCities[i] == nextCity)
        {
            return true;
        }
    }

    return false;
}

void getCheapestPrice(Matrix* matrix, size_t origin, size_t destination, size_t* visitedCities, size_t* visitedCitiesNumber, int64_t* totalPrice, Stack *lastPriceStack, Stack *cheapestPriceStack)
{
    for (size_t nextCity = 0; nextCity < matrix->numberOfCities; nextCity++)
    {
        int64_t price = *(matrix->arr + matrix->numberOfCities * origin + nextCity);

        if (price != -1)
        {
            bool cityVisited = isCityVisited(visitedCities, visitedCitiesNumber, nextCity);

            if (!cityVisited)
            {
                visitedCities[*(visitedCitiesNumber)] = origin;
                *visitedCitiesNumber = *visitedCitiesNumber + 1;

                *totalPrice += price;
                push(lastPriceStack, price);

                if (nextCity == destination)
                {
                    push(cheapestPriceStack, *totalPrice);
                    *totalPrice -= pop(lastPriceStack);
                }
                else
                {
                    getCheapestPrice(matrix, nextCity, destination, visitedCities, visitedCitiesNumber, totalPrice, lastPriceStack, cheapestPriceStack);
                }
            }
        }
    }

    if (getSize(lastPriceStack) > 0)
    {
        *totalPrice -= pop(lastPriceStack);
    }

    if (*visitedCitiesNumber > 0)
    {
        *visitedCitiesNumber = *visitedCitiesNumber - 1;
    }
}

int64_t findCheapestFlight(Matrix* matrix, char* origin, char* destination)
{
    size_t *visitedCities = (size_t*) malloc(matrix->numberOfCities * sizeof(size_t));
    size_t *visitedCitiesNumber = (size_t*) malloc(sizeof(size_t));
    int64_t *totalPrice = (int64_t*) malloc(sizeof(int64_t));

    *visitedCitiesNumber = 0;
    *totalPrice = 0;

    size_t originIndex, destinationIndex;

    for (size_t i = 0; i < matrix->numberOfCities; i++)
    {
        if (strcmp(matrix->cities[i], origin) == 0)
        {
            originIndex = i;
        }

        if (strcmp(matrix->cities[i], destination) == 0)
        {
            destinationIndex = i;
        }
    }

    Stack *lastPriceStack = createStack();
    Stack *cheapestPriceStack = createStack();
    getCheapestPrice(matrix, originIndex, destinationIndex, visitedCities, visitedCitiesNumber, totalPrice, lastPriceStack, cheapestPriceStack);

    int64_t lowestPrice = -1;
    uint64_t stackSize = getSize(cheapestPriceStack);

    for (size_t i = 0; i < stackSize; i++)
    {
        int64_t currentPrice = pop(cheapestPriceStack);

        if (currentPrice < lowestPrice || lowestPrice == -1)
        {
            lowestPrice = currentPrice;
        }
    }

    free(visitedCities);
    free(visitedCitiesNumber);
    free(totalPrice);
    destroyStack(lastPriceStack);
    destroyStack(cheapestPriceStack);

    return lowestPrice;
}
