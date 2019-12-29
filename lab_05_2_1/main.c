#include <stdio.h>

//Константа показывает максимальное количество строк
#define N_MAX 10

//Константа показывает максимальное количество столбцов
#define M_MAX 10

//Код ошибки если всё правильно
#define OK 0

//Код ошибки для ввода элемента
#define ERR_IO 1

//Код ошибки если размер строки и столбца превышаются заданный лимит
#define ERR_RANGE 2

//Константа для заполнения нулями массива
#define ZERO 0

/*Функция для ввода элементов в матрицу. Принимает саму матрицу, количество строк и столбцов.
Возвращает уже заполненную матрицу*/
int mtr_input(int a[][M_MAX], int *n, int *m)
{
    int rc = OK;
    printf("Input n, m: ");
    if (scanf("%d%d", n, m) == 2)
    {
        if (1 <= *n && *n <= N_MAX && 1 <= *m && *m <= M_MAX)
        {
            printf("Input elements:\n");
            for (int i = 0; rc == OK && i < *n; i++)
                for (int j = 0; rc == OK && j < *m; j++)
                    if (scanf("%d", &a[i][j]) != 1)
                        rc = ERR_IO;
        }
        else
            rc = ERR_RANGE;
    }
    else
        rc = ERR_IO;
    return rc;
}

/* Функция предназначенная для инициализации массива. Принимает две переменны:
сам массив и его длину. Возвращает нуль если массив успешно заполнен нулями.
*/
int array_initializing(int *array, int m)
{
    if (m < 0 || m > N_MAX)
        return ERR_RANGE;
    for (int i = 0; i < m; i++)
    {
        array[i] = ZERO;
    }
    return OK;
}

/*Функция для вывода введенного массива. Принимает сам массив и его размер.
Ничего не возвращает, а выводит сам массив*/
void array_print(int *array, int m)
{
    printf("Array: ");
    for (int i = 0; i < m; i++)
        printf("%d ", array[i]);
    printf("\n");
}

/*Функция, которая проходится по столбцам и смотрит, если в нем чередются числа по знаку, то в массив добавляет единицу, иначе нуль.
Эта функция ничего не возвращает, а добавляет единицу или нуль в массив. Принимает матрицу, его количество строк и столбцов.*/
/*void filling(int a[][M_MAX], int *array, int n, int m)
{
    int count;
    for (int j = 0; j < m; j++)
    {
        count = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i][j] > 0 && a[i + 1][j] < 0)
                count++;
            else if (a[i][j] < 0 && a[i + 1][j] > 0)
                count++;
            if (count == n - 1)
                array[j] = 1;
            else
            {
                if (n - i == 2)
                    array[j] = 0;
            }
        }
    }
}*/

/*void checking(int *new, int n, int *array, int i)
{
	int count = 0;
	for (int k = 0; k < n - 1; k++)
	{
		if (new[k] > 0 && new[k + 1] < 0)
			count++;
		else if (new[k] < 0 && new[k + 1] > 0)
			count++;
	}
	if (count == n - 1)
		array[i] = 1;
	else
		array[i] = 0;
}
*/


/*int checking(int *new, int n)
{
	int count = 0;
	for (int k = 0; k < n - 1; k++)
	{
		if (new[k] > 0 && new[k + 1] < 0)
			count++;
		else if (new[k] < 0 && new[k + 1] > 0)
			count++;
	}
	if (count == n - 1)
		return 1;
	else
		return 0;
}*/

void copy(int a[][M_MAX], int n, int m, int j, int *new)
{
	for (int i = 0; i < n; i++)
	{
		new[i] = a[i][j];
	}
}

int checking(int *new, int n)
{
	int count = 0;
    for (int k = 0; k < n - 1; k++)
    {
        if (new[k] > 0 && new[k + 1] < 0)
            count++;
        else if (new[k] < 0 && new[k + 1] > 0)
            count++;
		if (count == n - 1)
			return 1;
		else 
		{
			if (n - k == 2) 
				return 0;
		}
    }
	return -1;
}

void create_array(int a[][M_MAX], int *array, int n, int m)
{
	int new[N_MAX];
	for (int j = 0; j < m; j++)
	{
		copy(a, n, m, j, new);
		if (checking(new, n) == 1)
			array[j] = 1;
		else if (checking(new, n) == 0)
			array[j] = 0;
	}
}

int main(void)
{
    int a[N_MAX][M_MAX], array[N_MAX], n, m, rc, mc;
	setbuf(stdout, NULL);
    rc = mtr_input(a, &n, &m);
    mc = array_initializing(array, m);
    if ((rc == OK) && (mc == OK))
    {
		create_array(a, array, n, m);
        array_print(array, m);
    }
    else if ((rc == ERR_RANGE) || (mc == ERR_RANGE))
        printf("Size Error\n");
    else if (rc == ERR_IO)
        printf("Input Error\n");
    return rc;
}