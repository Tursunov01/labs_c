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

/*Функция для ввода элементов в матрицу. Принимает саму матрицу, количество строк и столбцов.
Возвращает уже заполненную матрицу*/
int mtr_input(int a[][M_MAX], int *n)
{
    int rc = OK;
    printf("Input n: ");
    if (scanf("%d", n) == 1)
    {
        if (1 <= *n && *n <= M_MAX)
        {
            printf("Input elements:\n");
            for (int i = 0; rc == OK && i < *n; i++)
                for (int j = 0; rc == OK && j < *n; j++)
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

void array_print(int *array, int n)
{
    printf("Array: ");
    for (int i = 0; i < n * 2; i++)
        printf("%d ", array[i]);
    printf("\n");
}



void create_array(int *array, int a[][M_MAX], int n)
{
	for (int i = 0; i < n; i++)
		array[i] = a[i][i];
	for (int i = 0; i < n; i++)
		array[n + i] = a[i][n - 1 - i];
}


int main(void)
{
    int a[N_MAX][M_MAX], array[N_MAX * 2], n, rc;
	setbuf(stdout, NULL);
    rc = mtr_input(a, &n);
    if ((rc == OK))
    {
		create_array(array, a, n);
        array_print(array, n);
    }
    else if ((rc == ERR_RANGE))
        printf("Size Error\n");
    else if (rc == ERR_IO)
        printf("Input Error\n");
    return rc;
}