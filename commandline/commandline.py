from __future__ import print_function
import sys
import mysql.connector
import subprocess

config = {
	'user': 'root',
	# 'password': 'password1',
	'password': 'localPass174',
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

columnList = ["emp_id", "emp_age", "emp_salary"]

def execute(query, values):
	your_query = query % values
	print("\n")
	print("Executing: {} ... ".format(query % values), end="")
	try:
		cursor.execute(query, values)
	except mysql.connector.Error as err:
		print("ERROR\nMySQL Error: {}\n".format(err))
		sys.exit(1)
	else:
		print("Success")
	print("----------------------------------------------------------\n")

def printQueryResults():
	rows = cursor.fetchall()
	if not rows:
		print("No employees were found.\n")
	else:
		row_format = "{:10s} {:10s} {:100s}"
		print(row_format.format(*columnList))
		print("----------------------------------------------------------")
		row_format = "{:<10d} {:<10d} {:100s}"
		for attributes in rows:
			print(row_format.format(*attributes))

def createSelectAllQuery():
	sql_query = "SELECT * FROM Employees"
	execute(sql_query, {})
	printQueryResults()

def createSelectEmployee(id):
	sql_query = "SELECT * FROM Employees WHERE id = %(emp_id)s"
	execute(sql_query, {"emp_id": id})
	printQueryResults()


def createSelectQuery(tokenList):
	if (tokenList[0] == "*"):
		createSelectAllQuery()
	elif (tokenList[0] == "SUM"):
			printf("This Option is not yet implemented.")
	else:
		createSelectEmployee(tokenList[0])

	# for salary in cursor:
	# 	# print(type(salary[0]))
	# 	decryptProgram = subprocess.Popen(['../encryption/decrypt', salary[0]], stdout=subprocess.PIPE)
	# 	decryptSalary = decryptProgram.stdout.read()
	# 	print(decryptSalary)

	# print(tokenList)

def createInsertQuery(tokenList):
	# guaranteed format: employeeId, employeeAge, employeeSalary
	emp_id = tokenList[0]
	emp_age = tokenList[1]
	emp_salary = tokenList[2]

	# Calling C file
	encryptProgram = subprocess.Popen(['../encryption/encrypt', emp_salary], stdout=subprocess.PIPE)
	encryptedSalary = encryptProgram.stdout.read()

	sql_query = "INSERT INTO Employees (id, age, salary) VALUES(%(emp_id)s, %(emp_age)s, %(emp_salary)s)"
	sql_values = {'emp_id': emp_id, 'emp_age': emp_age, 'emp_salary': encryptedSalary}	
	execute(sql_query, sql_values)
	
if __name__ == '__main__':
	while(True):
		statement = raw_input('Please enter your query: \n')

		# Parsing:
		tokenList = statement.split(" ")
		action = tokenList[0].upper()
		if action == 'SELECT':
			createSelectQuery(tokenList[1:])
		elif action == 'INSERT':
			createInsertQuery(tokenList[1:])
			cnx.commit()
		elif action == 'EXIT':
			break
		else:
			print ('Error: invalid query -- %s' % statement)

	cursor.close()
	cnx.close()
