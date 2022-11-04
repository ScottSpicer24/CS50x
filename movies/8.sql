--write a SQL query to list the names of all people who starred in Toy Story.

SELECT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE title = "Toy Story";

-- selecting FROM it(people) you cant JOIN it(people)
--can use one of its value after the ON tho
--think of JOIN like include stars then once JOIN again you can use a value from it on the next JOIN 