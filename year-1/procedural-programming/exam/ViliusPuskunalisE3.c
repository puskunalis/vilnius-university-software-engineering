#include <stdlib.h>

/*********************************************************************************************
Funkcija getPermutation sugeneruoja ir grąžina atsitiktinį keitinį. Keitinys - tai nesikartojančių skaičių nuo 1 iki size sąrašas. Ši funkcija gauna parametrą size ir sukuria dinaminį masyvą iš size elementų, atsitiktine tvarka užpildytą nesikartojančiais skaičiais nuo 1 iki size, taip, kad visi įmanomi variantai būtų vienodai tikėtini. Kad tai užtikrintų, funkcija naudoja tokį (ir ne kitokį) algoritmą: skaičių reikšmes į masyvą funkcija įterpinėja iš eilės, kas kartą naujam skaičiui eilėje atsitiktinai parinkdama poziciją. Kitaip tariant, funkcija pirmiausia įterpia 1, tada įterpia 2 (atsitiktinai pasirenka jam poziciją, vieną iš dviejų – ar įterpti prieš jau esantį 1, ar po jo), tada įterpia 3 (atsitiktinai pasirenka vieną iš trijų variantų – ar įterpti masyvo pradžioje, ar pabaigoje, ar tarp dviejų jau esančių elementų) ir t.t. Atsitiktiniam pozicijos numerio generavimui yra naudojama funkcija rand(), kuri anot dokumentacijos grąžina sveikąją reikšmę nuo 0 iki RAND_MAX; daroma prielaida, kad dar prieš paleidžiant funkciją atsitiktinių skaičių generatorius jau yra tinkamai inicializuotas. Funkcija grąžina nuorodą į dinaminio masyvo su keitinio elementais pradžią; jei dėl kokių nors priežasčių keitinio iš size elementų sugeneruoti negalima, funkcija grąžina NULL. Pavyzdžiai: getPermutation(3) grąžina 3 elementų masyvą, pvz. { 2, 1, 3 }; getPermutation(5) grąžina 5 elementų masyvą, pvz. { 5, 2, 3, 1, 4 }; getPermutation(0) grąžina NULL

*********************************************************************************************/
int* getPermutation (int size)
{
    if (size <= 0)
    {
        return NULL;
    }

    int *array = (int*) calloc(size, sizeof(int));

    for (int i = 1; i <= size; ++i)
    {
        int randomPos = rand() % i;

        if (*(array + randomPos) == 0)
        {
            *(array + randomPos) = i;
        }
        else
        {
            for (int j = size - 1; j > randomPos; --j)
            {
                *(array + j) = *(array + j - 1);
            }

            *(array + randomPos) = i;
        }
    }

    return array;
}
