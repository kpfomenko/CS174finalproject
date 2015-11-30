CC = gcc
#CFLAGS = -I
# Deps are the .h files
#DEPS =
OBJ = main.o

# Each .o file depends on the corresponding .c file and all the DEPS
# Generate the .o file (-c) with the same name as what's on the left of the ':'
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

encryption: main.o
	$(CC) -o encryption main.o

clean:
	rm *.o encryption