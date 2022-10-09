## Result

```
$ ./lab1
Allocating 30 bytes for array of char
Testing allocated chars
abcdefghijklmnopqrstuvwxyz{|}
Remaining allocator memory: 970

Allocating new data 16 * 16 bytes
abcdefghijklmnop
bcdefghijklmnopq
cdefghijklmnopqr
defghijklmnopqrs
efghijklmnopqrst
fghijklmnopqrstu
ghijklmnopqrstuv
hijklmnopqrstuvw
ijklmnopqrstuvwx
jklmnopqrstuvwxy
klmnopqrstuvwxyz
lmnopqrstuvwxyz{
mnopqrstuvwxyz{|
nopqrstuvwxyz{|}
opqrstuvwxyz{|}~
pqrstuvwxyz{|}~
Remaining allocator memory: 714

Allocating all remaining memory
Remaining allocator memory: 0

Deallocating 16 * 16 bytes
Remaining allocator memory: 256

Trying allocate 240 bytes
Remaining allocator memory: 16

Deallocating array of 30 bytes
Remaining allocator memory: 46
```
