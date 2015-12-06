from __future__ import print_function
import sys
import mysql.connector
import subprocess

config = {
	'user': 'root',
	'password': 'password1',
	# 'password': 'localPass174',
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
		raise
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
		for (id, age, encryptedSalary) in rows:
			# print("encryptedSalary %s" % encryptedSalary)
			decryptProgram = subprocess.Popen(['../encryption/decrypt', encryptedSalary], stdout=subprocess.PIPE)
			decryptedSalary = decryptProgram.stdout.read()
			print(row_format.format(id, age, decryptedSalary))

def createSelectAllQuery():
	sql_query = "SELECT * FROM Employees"

	try:
		execute(sql_query, {})
	except mysql.connector.Error:
		raise

	printQueryResults()

def createSelectEmployee(id):
	sql_query = "SELECT * FROM Employees WHERE id = %(emp_id)s"

	try:
		execute(sql_query, {"emp_id": id})
	except mysql.connector.Error:
		raise

	printQueryResults()

def printAggregateResult(title, result):
	print("{:10s}".format(title))
	print("----------------------------------------------------------")
	row_format = "{:100f}"
	if not result:
		print("NULL")
	else:
		for attributes in result:
			# print("result: %s" % result)
			print(*attributes)
			# print(row_format.format(*attributes))


def createSumQuery(statementPart):
	sql_query = "SELECT sum_he(salary) fROM Employees " + statementPart 
	if statementPart.find("GROUP BY") != -1:
		sql_query = "SELECT age, sum_he(salary) FROM Employees " + statementPart 

	try:
		execute(sql_query, {})
	except mysql.connector.Error:
		raise
	
	rows = cursor.fetchall()
	
	sumRows = []
	for i in range(len(rows)):
		# complete this when get sum_he working
		encryptedSum = rows[0]
		print("encryptedSum[0]: %s\n" % encryptedSum[0])
		print("type: %s\n" % type(str(encryptedSum[0])))
		encryptedSumStr = str(encryptedSum[0])
		print("type of str: %s\n" % type(encryptedSumStr))

		string = subprocess.check_output([encryptedSum[0]])

		decryptProgram = subprocess.Popen(['../encryption/decrypt',  str(encryptedSum[0])], stdout=subprocess.PIPE)
		decryptedSum = decryptProgram.stdout.read()
		sumRows.append((decryptedSum,))
	printAggregateResult("Sum", rows)

def createAvgQuery(statementPart):
	# get sum, decrypt sum, get count, then return sum/count
	sql_query = "SELECT sum_he(salary) FROM Employees " + statementPart 

	try:
		execute(sql_query, {})
	except mysql.connector.Error:
		raise

	rows = cursor.fetchall();
	if not rows:
		printAggregateResult("Avg", [])
	else:
		encryptedSum = rows[0]
		# print("encryptedSum: %s" % str(encryptedSum[0])) 
		# Calling C file
		# print(type(encryptedSum[0]))
		# decryptProgram = subprocess.Popen(['../encryption/decrypt', '%s' % str(encryptedSum[0])], stdout=subprocess.PIPE)
		# decryptedSum = decryptProgram.stdout.read()
		# print("decryptedSum: %s" % decryptedSum)
		decryptedSum = 21;
		sql_query = "SELECT COUNT(*) FROM Employees" 

		try:
			execute(sql_query, {})
		except mysql.connector.Error:
			raise

		countRows = cursor.fetchall()
		count = countRows[0]
		# print("count: %d\n" % count)
		avgRows = []
		for i in range(len(rows)):
			# rows[i][0] /= float(count[0])
			# print("decryptedSum: %d" % decryptedSum)
			# print("count[0]: %f" % float(count[0]))
			# print("decryptedSum/float(count[0]): %f" % (int(decryptedSum)/float(count[0])))
			average = (int(decryptedSum)/float(count[0]))
			avgRows.append((average,))
		printAggregateResult("Avg", avgRows)


def createSelectQuery(statement):
	statementList = statement.split(" ", 1)
	token = statementList[0]
	if (len(statementList) > 1):
		remainder = statement.split(" ", 1)[1]
	else:
		remainder = ""

	if (token == "*"):
		try:
			createSelectAllQuery()
		except mysql.connector.Error:
			raise
	elif (token == "SUM"):
		try:
			createSumQuery(remainder)
		except mysql.connector.Error:
			raise
	elif (token == "AVG"):
		try:
			createAvgQuery(remainder)
		except mysql.connector.Error:
			raise
	else:
		try:
			createSelectEmployee(token)
		except mysql.connector.Error:
			raise

def createInsertQuery(statement):
	# guaranteed format: employeeId, employeeAge, employeeSalary
	tokenList = statement.split(" ")
	emp_id = tokenList[0]
	emp_age = tokenList[1]
	emp_salary = tokenList[2]

	# Calling C file
	encryptProgram = subprocess.Popen(['../encryption/encrypt', emp_salary], stdout=subprocess.PIPE)
	encryptedSalary = encryptProgram.stdout.read()

	sql_query = "INSERT INTO Employees (id, age, salary) VALUES(%(emp_id)s, %(emp_age)s, %(emp_salary)s)"
	sql_values = {'emp_id': emp_id, 'emp_age': emp_age, 'emp_salary': encryptedSalary}	

	try:
		execute(sql_query, sql_values)
	except mysql.connector.Error:
		raise
	
if __name__ == '__main__':
	while(True):
		statement = raw_input('Please enter your query: \n')

		# Parsing:
		statementList = statement.split(" ", 1)
		action = statementList[0].upper()
		if (len(statementList) > 1):
			remainder = statement.split(" ", 1)[1]
		if action == 'SELECT':
			try:
				createSelectQuery(remainder)
			except mysql.connector.Error as err:
				print("ERROR\nMySQL Error: {}\n".format(err))
		elif action == 'INSERT':
			try:
				createInsertQuery(remainder)
			except mysql.connector.Error as err:
				print("ERROR\nMySQL Error: {}\n".format(err))
			cnx.commit()
		elif action == 'EXIT':
			break
		else:
			print ('Error: invalid query -- %s' % statement)

	cursor.close()
	cnx.close()
