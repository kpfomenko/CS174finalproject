from __future__ import print_function
import sys
import mysql.connector

config = {
	'user': 'root',
	'password': 'password1', 
	'host': '127.0.0.1', # Localhost. If your MySQL Server is running on your own computer.
	'port': '3306', # Default port on Windows/Linux is 3306. On Mac it may be 3307.
	'database': 'project',
}

try:
	cnx = mysql.connector.connect(**config)
	cursor = cnx.cursor()
except mysql.connector.Error as err:
	print("Connection Error: {}".format(err))
	sys.exit(1)

def execute(query, values):
	your_query = query % values
	print("Executing: {} ... ".format(query % values), end="")
	try:
		cursor.execute(query, values)
	except mysql.connector.Error as err:
		print("ERROR\nMySQL Error: {}\n".format(err))
		sys.exit(1)
	else:
		print("Success")

# Functions:
def createSelectQuery(tokenList):
	print(tokenList)

def createInsertQuery(tokenList):
	# guaranteed format: employeeId, employeeAge, employeeSalary
	emp_id = tokenList[0]
	emp_age = tokenList[1]
	emp_salary = tokenList[2]

	sql_query = "INSERT INTO Employees (id, age, salary) VALUES(%(emp_id)s, %(emp_age)s, %(emp_salary)s)"
	sql_values = {'emp_id': emp_id, 'emp_age': emp_age, 'emp_salary': emp_salary}	
	execute(sql_query, sql_values)
	
if __name__ == '__main__':
	statement = raw_input('Please enter your query: \n')
	# print 'Your statement: %s' % statement

	# Parsing:
	tokenList = statement.split(" ")
	# print 'Tokens: '
	# print tokenList
	action = tokenList[0].upper()
	if action == 'SELECT':
		createSelectQuery(tokenList[1:])
	elif action == 'INSERT':
		createInsertQuery(tokenList[1:])
	else:
		print ('Error: invalid action -- %s' % tokenList[0])

	cnx.commit()

	cursor.close()
	cnx.close()
