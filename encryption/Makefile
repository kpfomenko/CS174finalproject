CC = gcc
CFLAGS = -Wall -I /usr/local/include -I../libpaillier-0.8/
# Deps are the .h files
DEPS =
OBJ = encrypt.o decrypt.o createKeys.o 


# Each .o file depends on the corresponding .c file and all the DEPS
# Generate the .o file (-c) with the same name as what's on the left of the ':'
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

encrypt: encrypt.o
	$(CC) -o encrypt encrypt.o $(CFLAGS) -L/usr/local/lib -lpaillier -lgmp

decrypt: decrypt.o
	$(CC) -o decrypt decrypt.o $(CFLAGS) -L/usr/local/lib -lpaillier -lgmp

createKeys: createKeys.o
	$(CC) -o createKeys createKeys.o $(CFLAGS) -L/usr/local/lib -lpaillier -lgmp

clean:
	rm -f *.o encrypt decrypt createKeys