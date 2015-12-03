CC = gcc
CFLAGS = -Wall -I /usr/local/include -I../libpaillier-0.8/
# Deps are the .h files
DEPS =
OBJ = main.o


# Each .o file depends on the corresponding .c file and all the DEPS
# Generate the .o file (-c) with the same name as what's on the left of the ':'
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

encryption: main.o
	$(CC) -o encryption main.o $(CFLAGS) -L/usr/local/lib -lpaillier -lgmp

clean:
	rm *.o encryption