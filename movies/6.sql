--write a SQL query to determine the average rating of all movies released in 2012

--ORIGINAL(slightly diffrent results):SELECT ROUND(AVG(rating), 2) FROM ratings WHERE (SELECT year FROM movies WHERE year = 2012);
SELECT AVG(rating) FROM ratings
JOIN movies ON movies.id=ratings.movie_id
WHERE movies.year=2012;