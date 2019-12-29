#include <stdio.h>

#include <math.h>

// Показывает максимальное количество элементов в массиве
#define N_MAX 10

// Константа нужна для того чтобы показать что всё правильно
#define OK 0

// Код ошибки если введено более одного символа
#define ERR_IO 1

// Код ошибки если указанная переменная не попала в диапозон значений
#define ERR_RANGE 2

//Код ошибки если массив пуст
#define ERR_SIZE 3

// Код ошибки если в массиве нет отрицательных элементов
#define ERR_NEG 4

/* Функция предназначенная для ввода чисел в массив. Принимает две переменны:
сам массив и его размер. Возвращает нуль если массив успешно заполнен
*/
int array_input(int *a, int *n)
{
    printf("Input n: ");
    if (scanf("%d", n) != 1)
        return ERR_IO;
    if (*n < 0 || *n > N_MAX)
        return ERR_RANGE;
    printf("Input element: ");
    for (int i = 0; i < *n; i++)
    {
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    }
    return OK;
}

/* Функция для подсчета среднего арифметического всех отрицательных элементов.
Принимает два параметра: сам массив и его размер. Возвращает средне арифметическое отрицательных элементов.
*/
int calculate(const int *a, int n, float *result)
{
    int negative = 0, positive = 0;
    float s = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            s += a[i];
            negative++;
        }
        else
            positive++;
    }
    if (positive == n)
        return ERR_NEG;
    else
	{
        *result = s / negative;
		return OK;
	}
}

int main(void)
{
    int a[N_MAX];
    int n, rc = OK;
	float result = 0;
	setbuf(stdout, NULL);
    rc = array_input(a, &n);
    if (rc == OK)
    {
        if (n != 0)
        {
            if (calculate(a, n, &result) == ERR_NEG)
            {
                printf("There is no elements less than zero");
                rc = ERR_NEG;
            }
            else
                printf("%.5f", result);
        }
        else
        {
            printf("Need more elements than zero\n");
            rc = ERR_SIZE;
        }
    }
    else
    {
        printf("Error I/O");
        rc = ERR_IO;
    }
    return rc;
}