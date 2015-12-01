Use project;

SELECT SUM(salary) as NormalSum, mySum(salary) as MySum FROM Employees;