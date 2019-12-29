CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -ggdb -g3 
RM =rm

app.exe: main.o in_out.o sort.o
	$(CC) -o app.exe main.o in_out.o sort.o
main.o: main.c in_out.h constants.h structures.h sort.h 
	$(CC) $(CFLAGS) -c main.c
in_out.o: in_out.c structures.h constants.h  
	$(CC) $(CFLAGS) -c in_out.c
sort.o: sort.c structures.h
	$(CC) $(CFLAGS) -c sort.c

test.exe: test_system.o in_out.o sort.o
	$(CC) -o test.exe test_system.o in_out.o sort.o
test_system.o: test_system.c in_out.h sort.h structures.h constants.h
	$(CC) $(CFLAGS) -c test_system.c

clean:
	$(RM) *.o *.exe
