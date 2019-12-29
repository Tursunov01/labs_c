CC = gcc
CFLAGS = -std=c99 -Wall -Werror
RM = rm

app.exe: cdio_lib.so main.o
	$(CC) -o app.exe main.o cdio_lib.so 
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
test.exe: cdio_lib.so test_system.o
	$(CC) -o test.exe test_system.o cdio_lib.so
test_system.o: test_system.c
	$(CC) $(CFLAGS) -c test_system.c 	 
cdio_lib.so: cdio_lib.o
	$(CC) -shared -o cdio_lib.so cdio_lib.o
cdio_lib.o: cdio_lib.c
	$(CC) -$(CFLAGS) -fPIC -c cdio_lib.c
clean:
	$(RM) *.exe *.o *.so