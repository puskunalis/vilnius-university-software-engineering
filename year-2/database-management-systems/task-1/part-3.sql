-- Kiekvienam skaitytojui (vardas, pavardė) skaičius datų, kai jis paėmė bent vieną egzempliorių.
SELECT
    *
FROM
    (
        SELECT
            ROW_NUMBER() OVER (
                ORDER BY
                    COUNT(DISTINCT Stud.Egzempliorius.paimta) ASC
            ) AS id,
            Stud.Skaitytojas.vardas,
            Stud.Skaitytojas.pavarde,
            Stud.Skaitytojas.gimimas,
            Stud.Skaitytojas.adresas,
            COUNT(DISTINCT Stud.Egzempliorius.paimta) AS paimta
        FROM
            Stud.Skaitytojas
            JOIN Stud.Egzempliorius ON Stud.Egzempliorius.skaitytojas = Stud.Skaitytojas.nr
        GROUP BY
            Stud.Skaitytojas.nr
        ORDER BY
            paimta ASC
    ) t
WHERE
    MOD(id, 2) = 1;

-- Kiekvieneriems metams, kuriais buvo išleista bent viena knyga, ir kuriais buvo išleistos dvi ar daugiau knygų, visų ir vien tik paimtų egzempliorių skaičiai.
SELECT
    Stud.Knyga.metai,
    COUNT(Stud.Knyga.metai) AS visuegzemplioriuskaicius,
    t1.paimtuegzemplioriuskaicius
FROM
    Stud.Knyga
    JOIN Stud.Egzempliorius ON Stud.Egzempliorius.isbn = Stud.Knyga.isbn
    JOIN (
        SELECT
            Stud.Knyga.metai,
            COUNT(Stud.Knyga.metai) AS paimtuegzemplioriuskaicius
        FROM
            Stud.Knyga
            JOIN Stud.Egzempliorius ON Stud.Egzempliorius.isbn = Stud.Knyga.isbn
        WHERE
            paimta IS NOT NULL
        GROUP BY
            Stud.Knyga.metai
    ) t1 ON t1.metai = Stud.Knyga.metai
    JOIN (
        SELECT
            Stud.Knyga.Metai,
            COUNT(Stud.Knyga.Metai) AS isleistosknygos
        FROM
            Stud.Knyga
        GROUP BY
            Stud.Knyga.Metai
    ) t2 ON t2.metai = Stud.Knyga.metai
WHERE
    t2.isleistosknygos >= 2
GROUP BY
    Stud.Knyga.metai,
    t1.paimtuegzemplioriuskaicius,
    t2.isleistosknygos
ORDER BY
    Stud.Knyga.metai ASC;
