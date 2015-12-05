CC = gcc
CFLAGS = -Wall -I../libpaillier-0.8/ -I/usr/local/mysql/include/ -I/usr/include/mysql -L/usr/local/lib -lpaillier -lgmp
LIBFLAGS = -L./ -lsum

libsum.so: encyptedSum.c
	$(CC) -shared -fPIC $(CFLAGS) -o libsum.so encyptedSum.c

clean:
	rm -f *.o libsum.so

# compile for linux: gcc $(mysql_config --cflags) -shared -fPIC -o libsum.so encyptedSum.c paillier.c -lgmp
