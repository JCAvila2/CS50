SELECT ROUND(AVG(rating) + 0.005, 2) FROM ratings
WHERE movie_id IN (
    SELECT movie_id FROM movies
    WHERE year = 2012
);