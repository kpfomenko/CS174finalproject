CC = gcc
CFLAGS = -Wall -I../libpaillier-0.8/ -I/usr/local/mysql/include/
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

libsum.so: sum.o
	$(CC) -shared -o libsum.so sum.o

clean:
	rm -f *.o udf