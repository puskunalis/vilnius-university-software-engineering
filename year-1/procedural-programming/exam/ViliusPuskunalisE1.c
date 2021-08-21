/*********************************************************************************************
Funkcija hexToChar gauna skaičių digit, kurio reikšmė turi būti tarp 0 ir 15 imtinai, ir grąžina tą skaičių atitinkančio šešioliktainės sistemos skaitmens simbolio ASCII kodą. Parametras type nurodo raidės dydį, tiems atvejams, kai digit > 9, tokiu atveju, teigiama type reikšmė reiškia didžiąją, o neteigiama - mažąją. Funkcija grąžina simbolio ASCII kodą; jei digit nepatenka į nurodytus rėžius, funkcija grąžina 0. Pavyzdžiai: hexToChar(5,1) grąžina ’5’, hexToChar(10,1) grąžina ‘A’, hexToChar(0xF,-2) grąžina ‘f‘
*********************************************************************************************/
unsigned char hexToChar (int digit, char type)
{
    unsigned char skaiciai[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    unsigned char mRaides[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    unsigned char dRaides[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

    if (digit >= 0 && digit <= 9)
    {
        return skaiciai[digit];
    }
	else if (digit >= 0 && digit <= 15 && type <= 0)
    {
        return mRaides[digit - 10];
    }
	else if (digit >= 0 && digit <= 15 && type >= 1)
    {
        return dRaides[digit - 10];
    }
	else
    {
        return 0;
    }
}
