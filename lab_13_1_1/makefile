CC = gcc
CFLAGS = -std=c99 -Wall -Werror
RM = rm

app.exe: main.o libcdio.a
	$(CC) -o app.exe main.o libcdio.a
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
test.exe: test_system.o libcdio.a
	$(CC) -o test.exe test_system.o libcdio.a
test_system.o: test_system.c
	$(CC) $(CFLAGS) -c test_system.c
libcdio.a: cdio_lib.o
	ar rc libcdio.a cdio_lib.o
	#ranlib libcdio.a
cdio_lib.o: cdio_lib.c cdio_lib.h
	$(CC) $(CFLAGS) -c cdio_lib.c
clean:
	$(RM) *.exe *.o *.a