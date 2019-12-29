#компилятор
CC = gcc
RM = rm
CFLAGS = -std=c99 -Wall -Werror -ggdb

##описание для основной программы
app.exe: main.o in_out.o func.o delete.o insert.o multiply.o
	$(CC) -o app.exe main.o in_out.o func.o delete.o insert.o multiply.o
main.o: main.c constants.h in_out.h func.h delete.h insert.h multiply.h
	$(CC) $(CFLAGS) -c main.c
in_out.o: in_out.c constants.h 
	$(CC) $(CFLAGS) -c in_out.c
func.o: func.c constants.h in_out.h
	$(CC) $(CFLAGS) -c func.c
delete.o: delete.c constants.h func.h in_out.h
	$(CC) $(CFLAGS) -c delete.c
insert.o: insert.c constants.h func.h in_out.h
	$(CC) $(CFLAGS) -c insert.c
multiply.o: multiply.c constants.h in_out.h
	$(CC) $(CFLAGS) -c multiply.c	

##описание для запуска приложения тестирования
test.exe: test_system.o in_out.o func.o delete.o insert.o multiply.o
	$(CC) -o test.exe test_system.o in_out.o func.o delete.o insert.o multiply.o
test_system.o: test_system.c constants.h in_out.o func.o delete.o insert.o multiply.o
	$(CC) $(CFLAGS) -c test_system.c
dr.exe: draft.o in_out.o func.o
	$(CC) -o dr.exe draft.o in_out.o func.o
draft.o: draft.c constants.h in_out.o func.o 
	$(CC) $(CFLAGS) -c draft.c
##описание для удаления 
clean:
	$(RM) *.o *.exe
