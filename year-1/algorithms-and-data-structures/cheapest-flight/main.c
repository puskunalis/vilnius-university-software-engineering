#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main()
{
    Flight flights[] = {
        {"Kaunas", "Riga", 80},
        {"Palanga", "Vilnius", 40},
        {"Riga", "Palanga", 30},
        {"Riga", "San Francisco", 700},
        {"Riga", "Tokyo", 800},
        {"San Francisco", "Kaunas", 600},
        {"San Francisco", "Seattle", 300},
        {"Seattle", "Tokyo", 400},
        {"Tokyo", "Kaunas", 900},
        {"Tokyo", "Seattle", 500},
        {"Vilnius", "Palanga", 50},
        {"Vilnius", "Riga", 100},
    };

    size_t numberOfFlights = sizeof(flights) / sizeof(flights[0]);
    Matrix *matrix = createMatrix(flights, numberOfFlights);

    printMatrix(matrix);
    printCities(matrix);

    printf("%d\n", findCheapestFlight(matrix, "Vilnius", "Kaunas"));

    return 0;
}
