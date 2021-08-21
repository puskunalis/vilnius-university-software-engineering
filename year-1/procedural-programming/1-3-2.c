// Vilius Puskunalis 5 grupe 3 uzduotis
#include <stdio.h>

int main()
{
    int nelyginiai = 0, skaicius, suma;

    printf("Veskite skaicius, 0 zymi sekos pabaiga:\n");
    scanf("%d", &skaicius);

    while (skaicius != 0)
    {
        suma = 0;

        while (skaicius > 0)
        {
            suma += skaicius % 10;
            skaicius /= 10;
        }

        // Patikrinimui, ar teisingai surandama skaitmenu suma
        // printf("Skaitmenu suma: %d\n", suma);

        if (suma % 2 == 1)
        {
            ++nelyginiai;
        }

        scanf("%d", &skaicius);
    }

    printf("Nariai, kuriu skaitmenu suma nelygine: %d", nelyginiai);

    return 0;
}
