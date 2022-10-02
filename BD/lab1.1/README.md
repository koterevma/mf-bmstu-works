# Lab1

### Task
The task is to delete students from database having amount of 0's by all disciplines
equal to maximum amount of all students


### Details
- Database is called bd and small script `run_sql` is using [pass](https://www.passwordstore.org/)
  to get password for accessing database from encrypted storage
- Query for creation of table students located in create.sql file
- delete.sql query only prints students that should be deleted. To actually
  delete them, line `SELECT ...` should be substituted for `DELETE`

### Results

```
./run_sql select.sql

id      FIO     group_  d1      d2      d3      d4      d5      d6      d7      d8      d9
1       Koterev Maksim  K3-44B  0       0       0       0       0       0       0       0       0
2       Kuleshov Yaroslav       K3-44B  0       0       0       0       0       0       0       0       0
3       Grady Mcknight  K3-41B  0       0       0       0       0       0       0       0       0
4       Giovanni Henderson      K3-40B  0       0       0       0       0       0       0       0       5
5       Rocco Wiley     K3-46B  1       2       0       1       4       3       0       0       3
6       Miracle Navarro K3-42B  3       5       2       1       3       0       5       3       5
7       Carleigh Mcneil K3-46B  2       1       4       4       3       1       4       5       4
8       Justine Wilkerson       K3-40B  2       5       3       3       4       0       3       2       0
9       Jan Richards    K3-42B  2       2       1       4       0       1       3       1       0
10      Jefferson Marshall      K3-45B  2       3       0       3       0       0       1       3       2
11      Mackenzie Mathis        K3-41B  1       1       4       3       1       0       0       2       1
12      Kennedy Salas   K3-40B  2       1       4       1       4       2       4       3       3
13      Roland Carr     K3-42B  0       4       3       3       3       1       4       1       3
14      Helen Donaldson K3-40B  3       3       5       1       0       5       2       3       0
15      Haylie Ray      K3-44B  4       3       2       1       2       1       4       2       2
16      Quinton Knox    K3-42B  1       0       1       2       3       0       0       3       3
17      Esteban Maldonado       K3-44B  5       2       5       0       0       2       1       1       3
18      Jaida Cuevas    K3-42B  5       2       3       3       0       5       4       5       4
19      Jaime Lane      K3-40B  1       4       5       0       4       2       2       2       2
20      Ali Vincent     K3-40B  4       5       3       0       1       1       2       5       5
21      Alia Jackson    K3-46B  1       0       5       5       4       5       0       2       1
22      Madeline Sampson        K3-41B  5       0       5       1       4       3       3       5       1
23      Lillianna Bowman        K3-40B  4       5       0       1       3       4       1       5       1
24      Tyree Haney     K3-46B  1       3       0       1       1       3       4       1       4
25      Elian Heath     K3-41B  5       2       4       0       5       4       4       4       1
26      Lesly Leonard   K3-42B  5       5       2       1       2       5       3       2       3
27      Erick Kim       K3-45B  2       2       1       3       1       4       3       4       3
28      Sage Dunn       K3-42B  5       4       5       3       2       4       3       0       4
29      Branson Powell  K3-46B  4       0       4       2       3       2       4       1       4
30      Celia Gordon    K3-44B  5       4       0       4       0       5       4       3       2
31      Audrey Phillips K3-40B  2       2       1       4       3       3       0       4       1
32      Caleb Logan     K3-44B  4       4       5       1       2       5       4       4       4
33      Kieran Jacobs   K3-44B  3       0       1       4       1       2       2       4       4
34      Nola Palmer     K3-42B  3       0       1       4       3       4       4       3       1
35      Kylee Mason     K3-42B  3       0       5       1       2       4       3       2       2
36      Asia Soto       K3-46B  1       1       4       5       5       5       2       0       4
37      Sammy Blevins   K3-45B  3       3       0       5       1       3       5       1       4
38      Ana Yoder       K3-41B  5       0       4       2       2       0       3       4       1
39      Jocelyn Schwartz        K3-40B  5       2       5       5       4       4       3       1       0
40      Seamus Garza    K3-43B  2       3       5       3       5       1       0       2       5
41      Griffin Long    K3-43B  1       1       2       0       0       0       4       4       4
42      Neil Pruitt     K3-44B  0       2       3       5       1       1       5       5       5
43      Cortez Mcdaniel K3-41B  5       2       5       4       1       5       5       4       2
44      Draven Lee      K3-40B  0       0       1       1       4       0       0       1       1
45      Felipe Conley   K3-40B  4       5       3       4       5       0       3       0       0
46      Derrick Mathis  K3-41B  1       5       0       4       1       0       0       2       3
47      Adelaide Lewis  K3-45B  1       5       1       0       3       0       1       2       4
48      Tabitha Wilkins K3-45B  4       0       4       1       5       3       3       3       3
49      Kathleen Hinton K3-45B  2       3       3       5       3       3       1       1       5
50      Damari Murphy   K3-42B  1       3       4       0       1       0       3       3       3
51      Vicente Lutz    K3-44B  5       0       1       4       0       4       5       5       0
52      Kenna Golden    K3-40B  5       3       2       3       1       5       2       3       4
```

```
./run_sql delete.sql

FIO	group_
Koterev Maksim	K3-44B
Kuleshov Yaroslav	K3-44B
Grady Mcknight	K3-41B
```
Deleting people having all 9 zeros
