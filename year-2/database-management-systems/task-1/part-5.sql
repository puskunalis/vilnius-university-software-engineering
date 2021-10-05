-- Kiekvienai duomenų bazės lentelei - joje naudojamų stulpelių tipų skaičius.
SELECT
    table_name AS lentele,
    COUNT(DISTINCT data_type) AS tipai
FROM
    information_schema.columns
WHERE
    table_schema = 'stud'
GROUP BY
    table_name
ORDER BY
    tipai ASC;

-- Visi konkrečios lentelės stulpeliai, kuriems turi teisę naudoti užklausose einamasis naudotojas.
SELECT
    column_name AS stulpeliai
FROM
    information_schema.column_privileges
WHERE
    table_name = 'knyga'
    AND (
        grantee = 'PUBLIC'
        OR grantee = (
            SELECT
                session_user
        )
    )
ORDER BY
    stulpeliai ASC;

-- Visos lentelės, kuriose nėra nei vieno stulpelio, galinčio įgyti NULL reikšmę.
SELECT
    ROW_NUMBER() OVER () AS id,
    table_name AS lentele
FROM
    information_schema.columns
GROUP BY
    table_name
HAVING
    COUNT(
        CASE
            WHEN is_nullable = 'YES' THEN 1
        END
    ) = 0;
