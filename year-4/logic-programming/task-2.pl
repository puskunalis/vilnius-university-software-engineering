/*
    Vilius Puskunalis
    4 kursas, 4 grupe

    Saugomi duomenys:
        kelias(Miestas1, Miestas2, Atstumas).

    Variantai:
        1. Duotas miestus jungianciu keliu tinklas. Keliai vienakrypciai, nesudarantys ciklu.
           Kiekvienas kelias turi savo ilgi. Si informacija isreiskiama faktais kelias(Miestas1, Miestas2, Atstumas).
           Apibrezkite predikata "galima nuvaziuoti is miesto X i miesta Y": 
               1.6. pravaziavus ne daugiau kaip N tarpiniu miestu.

        6. Naturalieji skaiciai yra modeliuojami termais nul, s(nul), s(s(nul)), ... (zr. paskaitos medziaga).
           Apibrezkite predikata:
            6.1. dvieju skaiciu suma lygi treciajam skaiciui. Pavyzdziui:
                 ?- suma(s(s(s(nul))),s(s(nul)),Sum).
                 Sum = s(s(s(s(s(nul))))).

    Uzklausu pavyzdziai:
        suma(s(nul), s(nul), Sum). - Grazina Sum = s(s(nul)).
        suma(X, s(s(s(nul))), s(s(s(s(nul))))). - Grazina X = s(nul).
        galima_nuvaziuoti(las_vegas, Miestas2, 1). - Grazina Miestas2 = seattle, Miestas2 = san_diego, Miestas2 = san_antonio, Miestas2 = san_francisco, Miestas2 = dallas.
        galima_nuvaziuoti(san_francisco, san_diego, 0). - Grazina false.
        galima_nuvaziuoti(san_francisco, san_diego, 1). - Grazina true.
*/

kelias(seattle, san_francisco, 1000).
kelias(seattle, san_diego, 1200).
kelias(seattle, dallas, 3000).
kelias(las_vegas, seattle, 900).
kelias(las_vegas, san_diego, 120).
kelias(las_vegas, san_antonio, 1300).
kelias(dallas, san_antonio, 200).
kelias(dallas, houston, 180).
kelias(dallas, chicago, 1100).
kelias(atlanta, seattle, 5000).
kelias(atlanta, miami, 500).
kelias(los_angeles, san_diego, 50).
kelias(san_francisco, los_angeles, 400).
kelias(new_york, chicago, 600).
kelias(washington, new_york, 110).
kelias(boston, new_york, 100).

galima_nuvaziuoti(Miestas1, Miestas2, _) :- kelias(Miestas1, Miestas2, _).

galima_nuvaziuoti(Miestas1, Miestas2, TarpiniaiMiestai) :-
    TarpiniaiMiestai > 0,
    kelias(Miestas1, Miestas3, _),
    galima_nuvaziuoti(Miestas3, Miestas2, TarpiniaiMiestai-1).

suma(nul, Y, Y).
suma(s(X), Y, s(Sum)) :- suma(X, Y, Sum).
