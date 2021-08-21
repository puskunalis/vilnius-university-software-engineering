// Vilius Puskunalis 5 grupe 3 uzduotis
#include <stdio.h>

int main()
{
    int nelyginiai = 0, skaicius, skaicius2, suma;

    printf("Veskite skaicius, 0 zymi sekos pabaiga:\n");

    do
    {
        suma = 0;
        scanf("%d", &skaicius);
        skaicius2 = skaicius;

        while (skaicius2 > 0)
        {
            suma += skaicius2 % 10;
            skaicius2 /= 10;
        }

        // Patikrinimui, ar teisingai surandama skaitmenu suma
        // printf("Skaitmenu suma: %d\n", suma);

        if (suma % 2 == 1)
        {
            ++nelyginiai;
        }
    } while (skaicius != 0);

    printf("Nariai, kuriu skaitmenu suma nelygine: %d", nelyginiai);

    return 0;
}
