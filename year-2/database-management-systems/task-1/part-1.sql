-- Numeriai visų skaitytojų, kurie yra paėmę bent po vieną egzempliorių.
SELECT
    DISTINCT skaitytojas,
    Stud.Skaitytojas.vardas,
    Stud.Skaitytojas.pavarde
FROM
    Stud.Egzempliorius
    JOIN Stud.Skaitytojas ON Stud.Skaitytojas.nr = Stud.Egzempliorius.skaitytojas
WHERE
    skaitytojas IS NOT NULL
ORDER BY
    skaitytojas ASC;

-- Vardai ir pavardės visų skaitytojų, kurių numeris yra lyginis skaičius.
SELECT
    Stud.Skaitytojas.ak,
    Stud.Skaitytojas.vardas,
    Stud.Skaitytojas.pavarde,
    Stud.Skaitytojas.adresas
FROM
    Stud.Skaitytojas
WHERE
    MOD(Stud.Skaitytojas.nr, 2) = 0;
