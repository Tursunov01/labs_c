CC = gcc
CFLAGS = -std=c99 -Wall -Werror -w
RM = rm

test.exe: test_system.o func.o
	$(CC) -o test.exe test_system.o func.o
func.o: func.c constants.h func.h
	$(CC) $(CFLAGS) -c func.c
test_system.o: test_system.c constants.h func.h
	$(CC) $(CFLAGS) -c test_system.c
##описание для удаления 
clean:
	$(RM) *.o *.exe