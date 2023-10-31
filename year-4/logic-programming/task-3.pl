/*
    Vilius Puskunalis
    4 kursas, 4 grupe

    Saugomi duomenys:
        hex_to_bin(Ses, Dvej) - Sesioliktainis skaitmuo ir jam ekvivalentus dvejetainis skaicius.

    Variantai:
        1.10. sum(S,K1,K2) - skaiciu saraso S lyginiu elementu suma yra K1, o nelyginiu elementu suma yra K2.
        2.2. apjungti(SS,R) - sarasas R gaunamas is duotojo sarasu saraso SS, sujungus pastarojo sarasus i bendra sarasa. Giliuosius sarasus apdoroti nera butina.
        3.7. keisti(S,K,R) - duotas sarasas S. Duotas sarasas K, nusakantis keitini ir susidedantis is elementu pavidalo k(KeiciamasSimbolis, PakeistasSimbolis). R - rezultatas, gautas pritaikius sarasui S keitini K.
        4.6. sesiolik_i_dvejet(Ses,Dvej) - Ses yra skaicius vaizduojami sesioliktainiu skaitmenu sarasu. Dvej - tas pats skaiciaus, vaizduojamas dvejetainiu skaitmenu sarasu.

    Uzklausu pavyzdziai:
        sum([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K1, K2). - Grazina K1 = 30, K2 = 25.
        apjungti([[a, b], [c], [d, [e, f, [g]], h]], R). - Grazina R = [a, b, c, d, [e, f, [g]], h].
        keisti([a, b, c], [k(a, x), k(b, y)], R). - Grazina R = [x, y, c].
        sesiolik_i_dvejet([3, d], Dvej). - Grazina Dvej = [0, 0, 1, 1, 1, 1, 0, 1].
*/

yra_sarase(X, [X | _]) :- !.
yra_sarase(X, [_ | S]) :- yra_sarase(X, S).

sujungti([], S, S) :- !.
sujungti([X | S1], S2, [X | S3]) :- sujungti(S1, S2, S3).

% 1.10. sum(S,K1,K2)
even(N) :- mod(N, 2) =:= 0. 
odd(N) :- mod(N, 2) =:= 1. 
sum([], 0, 0).
sum([X | S], K1, K2) :-
    even(X),
    !,
    sum(S, NewK1, K2),
    K1 is NewK1+X.
sum([X | S], K1, K2) :-
    odd(X),
    !,
    sum(S, K1, NewK2),
    K2 is NewK2+X.

% 2.2. apjungti(SS,R)
apjungti([], []) :- !.
apjungti([X | SS], R) :-
    apjungti(SS, NewR),
    sujungti(X, NewR, R).

% 3.7. keisti(S,K,R)
keisti([], _, []) :- !.
keisti(S, [], S) :- !.
keisti([X | S], K, [Y | R]) :-
    yra_sarase(k(X, Y), K),
    !,
    keisti(S, K, R).
keisti([X | S], K, [X | R]) :-
    \+ yra_sarase(k(X, _), K),
    keisti(S, K, R).

% 4.6. sesiolik_i_dvejet(Ses,Dvej)
hex_to_bin(0, [0, 0, 0, 0]).
hex_to_bin(1, [0, 0, 0, 1]).
hex_to_bin(2, [0, 0, 1, 0]).
hex_to_bin(3, [0, 0, 1, 1]).
hex_to_bin(4, [0, 1, 0, 0]).
hex_to_bin(5, [0, 1, 0, 1]).
hex_to_bin(6, [0, 1, 1, 0]).
hex_to_bin(7, [0, 1, 1, 1]).
hex_to_bin(8, [1, 0, 0, 0]).
hex_to_bin(9, [1, 0, 0, 1]).
hex_to_bin(a, [1, 0, 1, 0]).
hex_to_bin(b, [1, 0, 1, 1]).
hex_to_bin(c, [1, 1, 0, 0]).
hex_to_bin(d, [1, 1, 0, 1]).
hex_to_bin(e, [1, 1, 1, 0]).
hex_to_bin(f, [1, 1, 1, 1]).
sesiolik_i_dvejet([], []) :- !.
sesiolik_i_dvejet([X | Ses], Dvej) :-
    hex_to_bin(X, DvejX),
    sesiolik_i_dvejet(Ses, DvejSes),
    sujungti(DvejX, DvejSes, Dvej).

sesiolik_i_dvejet2([0 | S], Res) :-
    !,
    sesiolik_i_dvejet2(S, Res).
sesiolik_i_dvejet2(S, S) :- !.
