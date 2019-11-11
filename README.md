# pg-gcd
 > pg extension to find gcd

### Install
```
make install && make installcheck
```

### Usage
```sql
CREATE EXTENSION gcd
SELECT gcd('{14, 21, 35, 42}'::int[]); //outputs 7
```
