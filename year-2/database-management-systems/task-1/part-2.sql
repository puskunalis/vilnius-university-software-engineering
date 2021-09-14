-- Visų konkretaus autoriaus, nurodyto vardu ir pavarde, visų jo parašytų knygų vertės vidurkis.
SELECT
    ROUND(AVG(Stud.Knyga.verte), 1) AS vidurkis
FROM
    Stud.Autorius
    JOIN Stud.Knyga ON Stud.Autorius.isbn = Stud.Knyga.isbn
WHERE
    CONCAT(Stud.Autorius.vardas, Stud.Autorius.pavarde) LIKE 'Pijus%Jonaitis';

-- Visų konkretaus autoriaus, nurodyto vardu ir pavarde, visų jo parašytų knygų puslapių vidurkis.
SELECT
    ROUND(AVG(Stud.Knyga.puslapiai), 0) AS vidurkis
FROM
    Stud.Autorius
    JOIN Stud.Knyga ON Stud.Autorius.isbn = Stud.Knyga.isbn
WHERE
    CONCAT(Stud.Autorius.vardas, Stud.Autorius.pavarde) LIKE 'Pijus%Jonaitis';
