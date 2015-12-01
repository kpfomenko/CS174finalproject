-- SHOW VARIABLES LIKE 'plugin_dir';

-- CREATE FUNCTION calc_distance_udf
-- 	RETURNS REAL
-- 	SONAME "calc_distance_udf.so";
Use airport;
CREATE FUNCTION testing_udf
	RETURNS REAL
	SONAME "testing_udf.so";
-- -- -- -- -- -- -- -- -- 
-- DROP FUNCTION testing_udf;

SELECT * FROM mysql.func;
-- DELETE FROM mysql.func WHERE name = "testing_udf";