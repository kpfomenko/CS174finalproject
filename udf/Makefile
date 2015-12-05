CC = gcc
CFLAGS = -Wall -I../libpaillier-0.8/ -I/usr/local/mysql/include/ -I/usr/include/mysql
LIBFLAGS = -lgmp

libsum.so: encyptedSum.c
	$(CC) $(mysql_config --cflags) -shared -fPIC $(CFLAGS) -o libsum.so encyptedSum.c paillier.c $(LIBFLAGS)

clean:
	rm -f *.o libsum.so

# compile for linux: gcc $(mysql_config --cflags) -shared -fPIC -o libsum.so encyptedSum.c paillier.c -lgmp -I/usr/local/mysql/include/
