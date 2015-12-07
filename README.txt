CS174A Databases Final Project
by Kateryna Fomenko and Deanna Hartsook

How to Set Up Database on AWS:

1. Compile SUM_HE shared library
	a. Go into udf directory
	b. Run the following commands:
		
		>> make
		>> sudo cp libsum.so /usr/lib/mysql/plugin/
		>> sudo service mysql restart

2. Set up Database
	a. Go into database directory
	b. Run following commands:
		>> mysql -u root -p
		>> source create.sql
		>> use project;
		>> GRANT ALL ON project.* TO root@'%' IDENTIFIED BY 'cs174$'
		>> source createUDF.sql
	c. Go to directory: /etc/mysql
		i. Open mysql.cnf
		ii. Find where it says "bind-address", and update the ip address to be the AWS localhost IP.

=============================================================

Running the Command Line Program:

1. Compile the encrypt/decrypt programs (on local computer)
	a. Go into encryption directory
	b. Run the following commands:
		>> make encrypt
		>> make decrypt

2. Run the python client (on local computer)
	a. Go into commandline directory
	b. Open commandline.py, and update the information in the config object, on line 6.
	b. Run the following command:
		>> python commandline.py
			[At this point you can begin entering queries in the form specified in the final_project.pdf ]
		i. To exit the client run the following command:
			>> exit
