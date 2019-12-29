#компилятор
CC = gcc
RM = rm
CFLAGS = -std=c99 -Wall -Werror -ggdb -lm -pedantic

##описание для основной программы
app.exe: main.o arr_struct.o delete.o func.o in_out.o insert.o sort.o
	$(CC) -o app.exe main.o arr_struct.o delete.o func.o in_out.o insert.o sort.o
main.o: main.c constants.h structures.h in_out.h arr_struct.h delete.h insert.h sort.h func.h 
	$(CC) $(CFLAGS) -c main.c
arr_struct.o: arr_struct.c constants.h structures.h in_out.h arr_struct.h
	$(CC) $(CFLAGS) -c arr_struct.c
delete.o: delete.c arr_struct.h constants.h structures.h func.h delete.h
	$(CC) $(CFLAGS) -c delete.c
func.o: func.c constants.h structures.h in_out.h sort.h func.h
	$(CC) $(CFLAGS) -c func.c
in_out.o: in_out.c constants.h structures.h func.h in_out.h
	$(CC) $(CFLAGS) -c in_out.c
insert.o: insert.c constants.h structures.h insert.h
	$(CC) $(CFLAGS) -c insert.c
sort.o: sort.c constants.h structures.h func.h sort.h
	$(CC) $(CFLAGS) -c sort.c
	
test.exe: test_system.o delete.o func.o insert.o sort.o in_out.o arr_struct.o
	$(CC) -o test.exe test_system.o delete.o func.o insert.o sort.o in_out.o arr_struct.o
test_system.o: test_system.c delete.h func.h insert.h sort.h constants.h structures.h in_out.h arr_struct.h 
	$(CC) $(CFLAGS) -c test_system.c
##описание для удаления 
clean:
	$(RM) *.o *.exe
