CC = gcc
CFLAGS = -Wall -I../libpaillier-0.8/ -I/usr/local/mysql/include/ -I/usr/include/mysql
LIBFLAGS = -L./ -lsum
# Deps are the .h files
DEPS = sum.h
OBJ = main.o

# Each .o file depends on the corresponding .c file and all the DEPS
# Generate the .o file (-c) with the same name as what's on the left of the ':'
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

udf: main.o libsum.so
	$(CC) -o udf main.o $(LIBFLAGS)

libsum.so: sum.c
	$(CC) -shared -fPIC $(CFLAGS) -o libsum.so sum.c  

clean:
	rm -f *.o udf