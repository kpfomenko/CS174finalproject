from __future__ import print_function
import sys

import mysql.connector

config = {
  'user': 'root',
  'password': 'localPass174', 
  'host': '127.0.0.1', # Localhost. If your MySQL Server is running on your own computer.
  'port': '3306', # Default port on Windows/Linux is 3306. On Mac it may be 3307.
  'database': 'airport',
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


if __name__ == '__main__':
  # Commit data
  cnx.commit()

  cursor.close()
  cnx.close()






# Functions:
def createSelectQuery(tokenList):
	print tokenList

def createInsertQuery(tokenList):
	# guaranteed format: employeeId, employeeAge, employeeSalary
	emp_id = tokenList[0]
	emp_age = tokenList[1]
	emp_salary = tokenList[2]

	sql_statement = "INSERT INTO Employees (id, age, salary) VALUES(%s, %s, %s)" % (emp_id, emp_age, emp_salary)
	print sql_statement
	return sql_statement


# Main: ---------------------------------------------
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
	print 'Error: invalid action -- %s' % tokenList[0]


