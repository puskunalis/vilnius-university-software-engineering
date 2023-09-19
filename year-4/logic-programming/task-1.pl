/*
    Vilius Puskunalis
    4 kursas, 4 grupe

    Saugomi duomenys:
        asmuo(Vardas, Lytis, Amzius, Pomegis);
        mama(Mama, Vaikas);
        pora(Vyras, Zmona).

    Variantai:
        5. vaikas(Vaikas, TevasMama) - Pirmasis asmuo (Vaikas) yra antrojo (TevasMama) vaikas;
        11. teta(Teta, SunenasDukterecia) - Pirmasis asmuo (Teta) yra antrojo (SunenasDukterecia) teta (tecio ar mamos sesuo);
        43. dar_pagyvens(Asmuo) - Asmuo Asmuo megsta kuria nors is sporto saku arba yra dar nepensinio amziaus (64 metai vyrams ir 63 metai moterims);
        44. at_suk(Asmuo, N) - Asmuo Asmuo atsvente N apvaliu sukakciu.

    Uzklausu pavyzdziai:
        vaikas(kazimieras, irena). - Grazina true, jei Kazimieras yra Irenos vaikas;
        vaikas(X, juozas). - Grazina visus Juozo vaikus;
        teta(marija, X). - Grazina visus Marijos sunenus ir dukterecias;
        dar_pagyvens(X). - Grazina visus asmenis, kurie megsta kuria nors is sporto saku arba yra dar nepensinio amziaus (64 metai vyrams ir 63 metai moterims);
        at_suk(X, 8). - Grazina visus asmenis, atsventusius 8 apvalias sukaktis;
        at_suk(X, 0). - Grazina visus asmenis, kuriems maziau, nei 10 metu.
*/

asmuo(kristina, moteris, 88, televizija).
asmuo(juozas, vyras, 87, golfas).
asmuo(ona, moteris, 55, tinklinis).
asmuo(jonas, vyras, 64, skaitymas).
asmuo(antanas, vyras, 56, tenisas).
asmuo(marija, moteris, 52, muzika).
asmuo(lina, moteris, 27, filmai).
asmuo(irena, moteris, 30, keliavimas).
asmuo(tomas, vyras, 29, radijas).
asmuo(kazimieras, vyras, 8, futbolas).

mama(kristina, jonas).
mama(kristina, marija).
mama(ona, lina).
mama(ona, irena).
mama(irena, kazimieras).

pora(juozas, kristina).
pora(jonas, ona).
pora(antanas, marija).
pora(tomas, irena).

sporto_saka(tinklinis).
sporto_saka(tenisas).
sporto_saka(golfas).
sporto_saka(futbolas).

tevas(Tevas, Vaikas) :-
    pora(Tevas, Mama),
    mama(Mama, Vaikas).

vaikas(Vaikas, Mama) :- mama(Mama, Vaikas).

vaikas(Vaikas, Tevas) :- tevas(Tevas, Vaikas).

sesuo(Sesuo, Asmuo) :-
    asmuo(Sesuo, moteris, _, _),
    Sesuo \= Asmuo,
    mama(Mama, Sesuo),
    mama(Mama, Asmuo).

teta(Teta, SunenasDukterecia) :-
    mama(Mama, SunenasDukterecia),
    sesuo(Teta, Mama).

teta(Teta, SunenasDukterecia) :-
    tevas(Tevas, SunenasDukterecia),
    sesuo(Teta, Tevas).

dar_pagyvens(Asmuo) :-
    asmuo(Asmuo, _, _, Pomegis),
    sporto_saka(Pomegis).

dar_pagyvens(Asmuo) :-
    asmuo(Asmuo, vyras, Amzius, _),
    Amzius < 64.

dar_pagyvens(Asmuo) :-
    asmuo(Asmuo, moteris, Amzius, _),
    Amzius < 63.

at_suk(Asmuo, N) :-
    asmuo(Asmuo, _, Amzius, _),
    N is div(Amzius, 10).
