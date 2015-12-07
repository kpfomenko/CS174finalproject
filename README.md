## CS174A Databases Final Project
by Kateryna Fomenko and Deanna Hartsook

### How to Set Up Database on AWS:

1. Compile SUM_HE shared library
  1. Go into udf directory
  2. Run the following commands:
	
	```
	>> make
	>> sudo cp libsum.so /usr/lib/mysql/plugin/
	>> sudo service mysql restart
	```

2. Set up Database
	1. Go into database directory
	2. Run following commands:

	 ```
	>> mysql -u root -p
	>> source create.sql
	>> use project;
	>> GRANT ALL ON project.* TO root@'%' IDENTIFIED BY 'cs174$'
	>> source createUDF.sql
	```
		
	3. Go to directory: /etc/mysql
		1. Open mysql.cnf
		2. Find where it says "bind-address", and update the ip address to be the AWS localhost IP.

=============================================================

### Running the Command Line Program:

1. Compile the encrypt/decrypt programs (on local computer)
	1. Go into encryption directory
	2. Run the following commands:

	```
	>> make encrypt
	>> make decrypt
	```
    
2. Run the python client (on local computer)
	1. Go into commandline directory
	2. Open commandline.py, and update the information in the config object, on line 6.
	3. Run the following command:
	
	```
	>> python commandline.py
	```
    
	[At this point you can begin entering queries in the form specified in the final_project.pdf ]
	1. To exit the client run the following command:
		
	```
	>> exit
	```
