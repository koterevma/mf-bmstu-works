SELECT  FIO, group_
FROM students
WHERE (d1 = 0) + (d2 = 0) + (d3 = 0) + (d4 = 0) + (d5 = 0) + (d6 = 0) + (d7 = 0) + (d8 = 0) + (d9 = 0) = (
    SELECT MAX((d1 = 0) + (d2 = 0) + (d3 = 0) + (d4 = 0) + (d5 = 0) + (d6 = 0) + (d7 = 0) + (d8 = 0) + (d9 = 0)) as max_d
    FROM students
)
