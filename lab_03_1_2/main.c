#include <stdio.h>

//Константа показывающая что все верно
#define OK 0

//Константа показывающая что введено неправильное количество параметров командной строки
#define ERR_WRONG_CMD 1

//Код ошибки если невозможно открыть файл
#define ERR_IO 2

//Код ошибки в которой не получилось вычислить среднее арифметическое мин и макс элемента*/
#define NO_RESULT 3

//Код ошибки если не получилось усатановить указатель на нужную позицию
#define ERR_POS 4

/*Функция которая находит минимальный элемент в файле.
Принимает файл и переменную в которую запишется минимальный элемент.
Возвращает код ошибки*/

int find_min(FILE* f, float *min)
{
    int status = NO_RESULT;
    float minn, number;
    if (fseek(f, 0, SEEK_SET) == 0)
    {
        if (fscanf(f, "%f", &minn) == 1)
        {
            status = OK;
            while (fscanf(f, "%f", &number) == 1)
            {
                if (number < minn)
                    minn = number;
            }
        }
    }
    else
        status = ERR_POS;
    *min = minn;
    return status;
}

/*Функция которая находит максимальный элемент в файле.
Принимает файл и переменную в которую запишется максимальный элемент.
Возвращает код ошибки*/

int find_max(FILE *f, float *max)
{
    int status = NO_RESULT;
    float maxx, number;
    if (fseek(f, 0, SEEK_SET) == 0)
    {
        if (fscanf(f, "%f", &maxx) == 1)
        {
            status = OK;
            while (fscanf(f, "%f", &number) == 1)
            {
                if (number > maxx)
                    maxx = number;
            }
        }
    }
    else
        status = ERR_POS;
    *max = maxx;
    return status;
}

/*Функция которая считает среднее арифметическое минимального и максимального элемента
Возвращает код ошибки. Принимает файл, мин и макс элемент и переменная в которую запишется результат*/
/*int find_average(FILE *f, float *min, float *max, float *average)
{
    int rc = OK;
    if (find_min(f, min) == OK && find_max(f, max) == OK)
        *average = (*min + *max) / 2;
    else
        rc = NO_RESULT;
    return rc;
}*/

/*Функция которая проходятся по элементам файла и
считает числа которые больше среднего арифметического мин и макс элемента.
Принимает файл и переменную в которую запишется это количество. Возвращает код ошибки*/
int check_count(FILE *f, int *count, int average)
{
    int status = NO_RESULT, amount = 0;
    float number;
    if (fseek(f, 0, SEEK_SET) == 0)
    {
        while (fscanf(f, "%f", &number) == 1)
        {
            status = OK;
            if (number > average)
                amount++;
        }
    }
    else
        status = ERR_POS;
    *count = amount;
    return status;
}


int main(int argc, char *argv[])
{
    FILE *f = NULL;
    int rc = OK, count;
    float min, max, average;
    if (argc != 2)
    {
        printf("main.exe test\n");
        return ERR_WRONG_CMD;
    }
    f = fopen(argv[1], "r");
    if (f)
    {
        if ((find_max(f, &max) == OK) && (find_min(f, &min) == OK))
        {
            average = (min + max) / 2;
            rc = check_count(f, &count, average);
            if (rc == OK)
            {
                rc = OK;
                printf("Number of elements which is big than average is %d\n", count);
            }
        }
        else
            rc = NO_RESULT;
    }
    else
    {
        printf("Can't open file\n");
        rc = ERR_IO;
    }
    fclose(f);
    return rc;
}
