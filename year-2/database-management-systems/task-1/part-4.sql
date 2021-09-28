-- Kiekvienai knygai (pavadinimas, ISBN) vyriausio jos skaitytojo vardas, pavardė ir gimimo data.
SELECT
    Stud.Knyga.pavadinimas,
    Stud.Knyga.isbn,
    Stud.Skaitytojas.vardas,
    Stud.Skaitytojas.pavarde,
    Stud.Skaitytojas.gimimas
FROM
    Stud.Knyga
    JOIN (
        SELECT
            Stud.Knyga.isbn,
            MIN(Stud.Skaitytojas.gimimas) as gimimas
        FROM
            Stud.Knyga
            JOIN Stud.Egzempliorius ON Stud.Egzempliorius.isbn = Stud.Knyga.isbn
            JOIN Stud.Skaitytojas ON Stud.Skaitytojas.nr = Stud.Egzempliorius.skaitytojas
        GROUP BY
            Stud.Knyga.isbn
    ) t ON Stud.Knyga.isbn = t.isbn
    JOIN Stud.Egzempliorius ON Stud.Egzempliorius.isbn = Stud.Knyga.isbn
    JOIN Stud.Skaitytojas ON Stud.Skaitytojas.nr = Stud.Egzempliorius.skaitytojas
    AND Stud.Skaitytojas.gimimas = t.gimimas
ORDER BY
    Stud.Knyga.pavadinimas ASC;

-- Numeris ir asmens kodas skaitytojų, kurie yra negrąžinę mažiau egzempliorių nei vidutiniškai visi skaitytojai yra negrąžinę. Greta pateikti ir tų skaitytojų negrąžintų egzempliorių skaičius.
SELECT
    Stud.Skaitytojas.nr,
    Stud.Skaitytojas.ak,
    t.paimti
FROM
    (
        SELECT
            Stud.Egzempliorius.skaitytojas,
            COUNT(Stud.Egzempliorius.skaitytojas) as paimti
        FROM
            Stud.Egzempliorius
        WHERE
            Stud.Egzempliorius.skaitytojas IS NOT NULL
        GROUP BY
            Stud.Egzempliorius.skaitytojas
    ) t
    JOIN Stud.Skaitytojas ON Stud.Skaitytojas.nr = t.skaitytojas
WHERE
    paimti < (
        SELECT
            AVG(paimti) AS vidurkis
        FROM
            (
                SELECT
                    Stud.Egzempliorius.skaitytojas,
                    COUNT(Stud.Egzempliorius.skaitytojas) AS paimti
                FROM
                    Stud.Egzempliorius
                WHERE
                    Stud.Egzempliorius.skaitytojas IS NOT NULL
                GROUP BY
                    Stud.Egzempliorius.skaitytojas
            ) t
    )
ORDER BY
    Stud.Skaitytojas.nr ASC;
