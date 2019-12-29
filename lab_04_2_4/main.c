#include <stdio.h>

// Показывает максимальное количество элементов в массиве
#define N_MAX 10

// Константа нужна для того чтобы показать что всё правильно
#define OK 0

// Код ошибки если введено более одного символа
#define ERR_IO 1

// Код ошибки если указанная переменная не попала в диапозон значений
#define ERR_RANGE 2

// Код ошибки, вызывается код размер массива равен нулю
#define ERR_SIZE 3

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

/* Функция для вывода массива. Принимает также 2 параметра: это сам массив и его размер.
Ничего не возвращает.
*/
void array_output(const int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

/*Функция для сортировки массива выбором по возрастанию.
Принимает 2 параметра: сам массив и его размер. Ничего не возвращает, но сортирует сам массив.
*/
void sort(int *a, int n)
{
    int index, index_now;
    for (int i = 0; i < n; i++)
    {
        index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[index])
                index = j;
        }
        index_now = a[index];
        a[index] = a[i];
        a[i] = index_now;
    }
}

void sortic(int *a, int n)
{
	int tmp = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

void flaggy(int *a, int n)
{
	int tmp = 0, flag = 0;
	do
	{
		flag = 0;
		for (int i = 1; i < n ; i++)
		{
			if (a[i] < a[i - 1])
			{
				tmp = a[i - 1];
				a[i - 1] = a[i];
				a[i] = tmp;
				flag = 1;
			}
		}
	}
	while (flag);
}

int main(void)
{
    int a[N_MAX];
    int n, rc = OK;
	setbuf(stdout, NULL);
    rc = array_input(a, &n);
    if (rc == OK)
    {
        if (n != 0)
        {
            flaggy(a, n);
            array_output(a, n);
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
