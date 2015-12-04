
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


