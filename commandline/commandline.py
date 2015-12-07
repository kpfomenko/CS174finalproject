from __future__ import print_function
import sys
import mysql.connector
import subprocess

config = {
	'user': 'root',
	'password': 'cs174$',
	# 'password': 'password1',
	# 'password': 'localPass174',
	# 'host': '127.0.0.1', # Localhost. If your MySQL Server is running on your own computer.
	'host': '54.67.69.244',
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
	# print("\n")
	# print("Executing: {} ... ".format(query % values), end="")
	try:
		cursor.execute(query, values)
	except mysql.connector.Error as err:
		raise
	# else:
	# 	print("Success")
	# print("----------------------------------------------------------\n")

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

def printAggregateResult(titles, result):
	print("\n")
	row_format = "{:10s}" * len(titles)
	print(row_format.format(*titles))
	print("----------------------------------------------------------")

	# if not result:
	# 	if not ti
	# 	print(row_format.format( "NULL"))
	# else:
	for attributes in result:
		print(row_format.format(*attributes))
	print("\n")


def createSumQuery(statementPart):
	sql_query = "SELECT SUM_HE(salary) FROM Employees " + statementPart
	if statementPart.find("GROUP BY") != -1:
		sql_query = "SELECT age, sum_he(salary) FROM Employees " + statementPart
		titles = ["Age", "Sum"]
		sumRows = [["NULL", "NULL"]]
	else:
		titles = ["Sum"]
		sumRows = [["NULL"]]

	try:
		execute(sql_query, {})
	except mysql.connector.Error:
		raise
	
	rows = cursor.fetchall()
	age = ''
	if len(rows) > 0:
		sumRows = []		
	for i in range(len(rows)):
		encryptedSumResults = rows[i]
		if len(encryptedSumResults) == 2:
			# GROUP BY age
			encryptedSum = rows[i][1]
			age = rows[i][0]
		else:
			encryptedSum = rows[i][0]

		encryptedSumString = `str(encryptedSum)`
		encryptedSumString = encryptedSumString.split("\\")[0]
		encryptedSumString = encryptedSumString[1:]

		decryptProgram = subprocess.Popen(['../encryption/decrypt',  encryptedSumString], stdout=subprocess.PIPE)
		decryptedSum = decryptProgram.stdout.read()

		if age:
			sumRows.append((str(age), decryptedSum))
		else:
			sumRows.append((decryptedSum,))
	printAggregateResult(titles, sumRows)

def createAvgQuery(statementPart):
	# get sum, decrypt sum, get count, then return sum/count
	sql_query = "SELECT SUM_HE(salary) fROM Employees " + statementPart
	if statementPart.find("GROUP BY") != -1:
		sql_query = "SELECT age, SUM_HE(salary) FROM Employees " + statementPart
		titles = ["Age", "Avg"]
		avgRows = [["NULL", "NULL"]]
	else:
		titles = ["Avg"]
		avgRows = [["NULL"]]

	try:
		execute(sql_query, {})
	except mysql.connector.Error:
		raise
	rows = cursor.fetchall()
	age = ''

	sql_query = "SELECT COUNT(*) FROM Employees " + statementPart

	try:
		execute(sql_query, {})
	except mysql.connector.Error:
		raise

	countRows = cursor.fetchall()

	count = countRows[0][0]
	if count == 0:
		printAggregateResult(titles, avgRows)
		return
	else:
		avgRows = []

	for i in range(len(rows)):
		encryptedSumResults = rows[i]
		count = countRows[i][0]
		if len(encryptedSumResults) == 2:
			# GROUP BY age
			encryptedSum = rows[i][1]
			age = rows[i][0]
		else:
			encryptedSum = rows[i][0]

		encryptedSumString = `str(encryptedSum)`
		encryptedSumString = encryptedSumString.split("\\")[0]
		encryptedSumString = encryptedSumString[1:]

		decryptProgram = subprocess.Popen(['../encryption/decrypt',  encryptedSumString], stdout=subprocess.PIPE)
		decryptedSum = decryptProgram.stdout.read()

		average = (int(decryptedSum)/float(count))

		if age:
			avgRows.append((str(age), str(average)))
		else:
			avgRows.append((str(average),))
	printAggregateResult(titles, avgRows)

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
