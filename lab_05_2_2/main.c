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

//Константа вызывается если некоторое условие верно
#define TRUE 1

//Константа вызывается если некоторое условие неверно
#define FALSE 0

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

/*Функция для вывода матрицу Принимает матрицу, количество строк и столбцов.
Ничего не возвращает, а выводит матрицу*/
void mtr_print(int a[][M_MAX], int n, int m)
{
    printf("Matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
/* Функция проверяет число на четность и нечетность.
Возвращает TRUE если число нечетное иначе FALSE*/
int check(int summa)
{
    if ((summa) % 2 == 1)
        return TRUE;
    else
        return FALSE;
}

/*Функция складывает все цифры числа вызывает функцию check
Принимает проверяемое число. Возвращает результат функции check*/
int summing(int number)
{
    int end, start, summa = 0;
    if (number < 0)
        number = number * (-1);
    end = number % 10;
    summa = end;
    while (number > 9)
    {
        number = number / 10;
        start = number % 10;
        summa = summa + start;
    }
    return summa;
}

/* Функция которая проходится по всем элементам строки и передает эти элементы в функцию summing.
Принимает матрицу, количество столбцов, и текущую позицию строки матрицы.*/
int pass(int a[][M_MAX], int m, int i)
{
    int count = 0, result;
    for (int j = 0; j < m; j++)
    {
        result = summing(a[i][j]);
		if (check(result))
            count++;
    }
    return count;
}

/* Функция которая сдвигает строки на одну позицию вниз, тем самым освобождая место для новой строки.
Принимает матрицу, текущую позицию строки, количество столбцов, и текущее количество строк.*/
void replace(int a[][M_MAX], int i, int m, int tmp_size)
{
    for (int k = tmp_size ; k > i ; k--)
        for (int t = 0; t < m; t++)
            a[k][t] = a[k - 1][t];
}

/*Функция которая вставляет новую строку в матрицу на позицию i, состоящую из -1.
Принимает матрицуб количество столбцов и позицию для строки куда нужно вставить строку.*/
void add(int a[][M_MAX], int m, int i)
{
    for (int q = 0; q < m; q++)
        a[i][q] = -1;
}

/* Функция которая находит строку где есть хотябы 2 числа, сумма цифра которого нечетное число,
после добаляет строку из -1 в предыдущую строку матрицы.
Принимает матрицу число строк и столбцов и переменную в которой хранится текущий размер строк матрицы.
Эта функция вызывает с себе несколько функций, а именно функция которая проходится по строкам,
функция которая сдвигает строки и функция которая вставляет новую строку из -1.*/
void forming(int a[][M_MAX], int n, int m, int *tmp_size)
{
    *tmp_size = n;
    for (int i = 0; i < *tmp_size ; i++)
    {
        if (pass(a, m, i) >= 2)
        {
            *tmp_size += 1;
            replace(a, i, m, *tmp_size);
            add(a, m, i);
            i++;
        }
    }
}

int main(void)
{
    int a[N_MAX][M_MAX], n, m, rc, tmp_size;
	setbuf(stdout, NULL);
    rc = mtr_input(a, &n, &m);
    if (rc == OK)
    {
        forming(a, n, m, &tmp_size);
        mtr_print(a, tmp_size, m);
    }
    else if (rc == ERR_RANGE)
        printf("Size Error\n");
    else if (rc == ERR_IO)
        printf("Input Error\n");
    return rc;
}
