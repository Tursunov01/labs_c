CC = gcc
CFLAGS = -std=c99 -Wall -Werror
RM = rm


app.exe: main.o cdio.so
	$(CC) -o app.exe main.o -ldl
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
cdio.so: cdio_lib.o
	$(CC) -shared cdio_lib.o -o cdio.so  
cdio_lib.o: cdio_lib.c
	$(CC) $(CFLAGS) -fPIC -c cdio_lib.c


test.exe: test_system.o cdio.so 
	$(CC) -o test.exe test_system.o -ldl
test_system.o: test_system.c
	$(CC) $(CFLAGS) -c test_system.c

clean:
	$(RM) *.exe *.o *.so