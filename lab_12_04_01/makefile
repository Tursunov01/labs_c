#компилятор
CC = gcc
RM = rm
CFLAGS = -std=c99 -Wall -Werror -ggdb

##описание для основной программы
app.exe: main.o in_out.o func.o operations.o
	$(CC) -o app.exe main.o in_out.o func.o operations.o
main.o: main.c in_out.h func.h operations.h
	$(CC) $(CFLAGS) -c main.c
in_out.o: in_out.c constants.h structure.h
	$(CC) $(CFLAGS) -c in_out.c
func.o: func.c in_out.h operations.h constants.h structure.h
	$(CC) $(CFLAGS) -c func.c
operations.o: operations.c in_out.h func.h constants.h structure.h
	$(CC) $(CFLAGS) -c operations.c

test.exe: test_system.o func.o operations.o in_out.o
	$(CC) -o test.exe test_system.o func.o operations.o in_out.o
test_system.o: test_system.c constants.h structure.h func.o operations.o in_out.o
	$(CC) $(CFLAGS) -c test_system.c
##описание для удаления 
clean:
	$(RM) *.o *.exe
