#include <stdio.h>

//константа показывающая что всё хорошо
#define OK 0

//Константа отвечающая за неправильный ввод
#define NO_RESULT -1


/*Эта функция ищет порядковый номер максимального элемента,
 возвращает статус, т.е если всё верно то вернется 0 иначе -2.
принимает эта функция файл, и countmax, в которую перезапишется значение порядкового номера*/

int process(FILE* f, int *countmax)
{
    int status = NO_RESULT, count = 1, number, maxx;
    if (fscanf(f, "%d", &maxx) == 1)
    {
		*countmax = count;
		count++;
		status = OK;
        while (fscanf(f, "%d", &number) == 1)
        {
            if (number > maxx)
            {
                maxx = number;
                *countmax = count;
            }
            count++;
        }
    }
    return status;
}

int main(void)
{
    FILE* f = stdin;
    int countmax, status = OK;
    setbuf(stdout, NULL);
    printf("Input numbers per one: ");
	status = process(f, &countmax);
    if (status == OK)
		printf("Position is %d", countmax);
    else
        printf("Input error!");
    return status;
}
