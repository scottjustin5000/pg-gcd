-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION gcd" to load this file. \quit
CREATE OR REPLACE FUNCTION gcd(anyarray) RETURNS integer
AS 'gcd', 'gcd'
LANGUAGE C IMMUTABLE STRICT;