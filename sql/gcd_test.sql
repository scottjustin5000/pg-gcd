CREATE EXTENSION gcd;
SELECT gcd('{4, 6, 8, 16}'::int[]);
SELECT gcd('{14, 21, 35, 42}'::int[]);