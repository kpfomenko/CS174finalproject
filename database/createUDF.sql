-- DROP FUNCTION mySum

CREATE AGGREGATE FUNCTION mySum RETURNS INTEGER SONAME 'libsum.so';