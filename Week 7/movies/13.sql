SELECT name from people
WHERE id IN (
    SELECT person_id FROM stars
    WHERE movie_id IN (
        SELECT id from movies
        WHERE id IN (
            SELECT movie_id FROM stars
            WHERE person_id IN (
                SELECT id FROM people
                WHERE name = "Kevin Bacon"
            )
        )
    )
)
AND NOT name = "Kevin Bacon";