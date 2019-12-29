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

//Константа, используемая при сортировки. Вызывается если некоторое условие верно
#define TRUE 1

//Константа, используемая при сортировки. Вызывается если некоторое условие неверно
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

/*Функция для вывода матрицыю Принимает матрицу, количество строк и столбцов.
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

/*Функция которая перемножает элементы заданной строки, а также элементы следующей строки.
Сравнивает два значения и возвращает TRUE если последующая строка меньше текущей строки иначе возвращает FALSE.
Принимает матрицу, количество столбцов и текущую позицию строки.*/
/*int multiply(int a[][M_MAX], int m, int i)
{
    int count_row = 1, count_next_row = 1;
    for (int j = 0; j < m; j++)
    {
        count_row *= a[i][j];
        count_next_row *= a[i + 1][j];
    }
    if (count_next_row < count_row)
        return TRUE;
    else
        return FALSE;
}*/

/*Функция которая переставляет строки матрицы и возвращает flag = TRUE после одной успешной перестановки.
Принимает матрицу, количество столбцов и текущую позицию строки, и значение флага flag = FALSE.*/
/*int replace(int a[][M_MAX], int m, int i, int flag)
{
    int save;
    for (int k = 0; k < m; k++)
    {
        save = a[i][k];
        a[i][k] = a[i + 1][k];
        a[i + 1][k] = save;
        flag = TRUE;
    }
    return flag;
}*/

/*Функция для сортировки строк матрицы по возрастанию.
Принимает требуемый для сортировки матрица, количество строк и столбцов.*/
/*void sorting(int a[][M_MAX], int n, int m)
{
    int flag, edge;
    edge = n - 1;
    flag = TRUE;
    while (flag)
    {
        flag = FALSE;
        for (int i = 0; i < edge; i++)
        {
            if (multiply(a, m, i))
                flag = replace(a, m, i, flag);
        }
        edge -= 1;
    }
}*/

int changing(int *a1, int *a2, int m)
{
	int tmp;
	for (int i = 0; i < m; i++)
	{
		tmp = a1[i];
		a1[i] = a2[i];
		a2[i] = tmp;
	}
	return 1;
}

int multiply(int a[][M_MAX], int m, int j)
{
	int count = 1;
	for (int i = 0; i < m; i++)
	{
		count = count * a[j][i];
	}
	return count;
}

int mul(const int *a1, int m)
{
	int count = 1;
	for (int i = 0; i < m; i++)
		count *= a1[i];
	return count;
}

/*int replace(int a[][M_MAX], int m, int i)
{
	int row_1, row_2;
	row_1 = mul(a[i], m);
	row_2 = mul(a[i + 1], m);
	if (row_1 > row_2)
	{
		changing(a[i], a[i + 1], m);
	}
	return 1;
}*/

void sort(int a[][M_MAX], int n, int m)
{
	int flag = 1, edge = n - 1;
	while (flag)
	{
		flag = 0;
		for (int i = 0; i < edge; i++)
		{
			if (mul(a[i], m) > mul(a[i + 1], m))
				flag = changing(a[i], a[i + 1], m);
		}
		edge--;
	}
}

int main(void)
{
    int a[N_MAX][M_MAX], n, m, rc;
	setbuf(stdout, NULL);
    rc = mtr_input(a, &n, &m);
    if (rc == OK)
    {
        sort(a, n, m);
        mtr_print(a, n, m);
    }
    else if (rc == ERR_RANGE)
        printf("Size Error\n");
    else if (rc == ERR_IO)
        printf("Input Error\n");
    return rc;
}