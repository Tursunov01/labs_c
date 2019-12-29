CC = gcc
CFLAGS = -std=c99 -Wall -Werror -ggdb
RM = rm

app.exe: main.o cdio.o
	$(CC) -o app.exe main.o cdio.o
main.o: main.c constants.h structures.h cdio.h
	$(CC) $(CFLAGS) -c main.c
cdio.o: cdio.c constants.h structures.h cdio.h
	$(CC) $(CFLAGS) -c cdio.c
clean:
	$(RM) *.exe *.o