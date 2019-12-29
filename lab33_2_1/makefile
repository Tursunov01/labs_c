CC = gcc
CFLAGS = -std=c99 -Wall -Werror -ggdb
RM = rm

app.exe: main.o in_out.o
	$(CC) -o app.exe main.o in_out.o
in_out.o: in_out.c constants.h structures.h in_out.h
	$(CC) $(CFLAGS) -c in_out.c
main.o: main.c constants.h structures.h in_out.h
	$(CC) $(CFLAGS) -c main.c
clean:
	$(RM) *.exe *.o