#компилятор
CC = gcc
RM = rm
CFLAGS = -std=c99 -Wall -Werror -ggdb

##описание для основной программы
app.exe: main.o input_output.o secondary_functions.o forming_new_array.o
	$(CC) -o app.exe main.o secondary_functions.o input_output.o forming_new_array.o -lm
main.o: main.c constants.h input_output.h secondary_functions.h forming_new_array.h
	$(CC) $(CFLAGS) -c main.c
input_output.o: input_output.c constants.h 
	$(CC) $(CFLAGS) -c input_output.c 
secondary_functions.o: secondary_functions.c constants.h
	$(CC) $(CFLAGS) -c secondary_functions.c
forming_new_array.o: forming_new_array.c constants.h
	$(CC) $(CFLAGS) -c forming_new_array.c

##описание для запуска приложения тестирования
test.exe: test_system.o secondary_functions.o forming_new_array.o
	$(CC) -o test.exe test_system.o secondary_functions.o forming_new_array.o
test_system.o: test_system.c constants.h secondary_functions.h forming_new_array.h
	$(CC) $(CFLAGS) -c test_system.c
##описание для удаления 
clean:
	$(RM) *.o *.exe