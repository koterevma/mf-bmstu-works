## Task

* **Calculate any math function using multiple processes in C**

## Result

```
$ ./lab2
result in p1 = 7.453560
Child 1 done
result from p2 = 13.628291
Child 2 done
Parent recieved from pipe: 7.453560
Parent recieved from pipe: 13.628291
Result of child threads = 21.081851
Result calculated only in parent thread = 21.081851
```

### Result from wolframalpha

- integral(0, 10, sqrt(x)) = 21.0818510677892
- integral(0, 5,  sqrt(x)) = 7.45355992499930
- integral(5, 10, sqrt(x)) = 13.6282911427899
