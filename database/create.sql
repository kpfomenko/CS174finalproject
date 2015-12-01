-- create.sql by Katya Fomenko and Deanna Hartsook
DROP DATABASE IF EXISTS project;
CREATE DATABASE project;
USE project;

CREATE TABLE Employees (
	id INTEGER,
	age INTEGER,
	salary INTEGER NOT NULL,
	PRIMARY KEY(id)
);

-- CREATE TABLE Employees (
-- 	id INTEGER,
-- 	age INTEGER,
-- 	salary TEXT NOT NULL,
-- 	PRIMARY KEY(id)
-- );