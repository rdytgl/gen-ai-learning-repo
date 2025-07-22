SELECT DISTINCT movies.title
FROM movies
JOIN people ON people.id = stars.person_id
JOIN stars ON stars.movie_id = movies.id
JOIN ratings ON ratings.movie_id = movies.id
WHERE name = 'Chadwick Boseman'
ORDER BY rating DESC LIMIT 5;
