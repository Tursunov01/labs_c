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

//Константа вызывающаяся если массив состоит только из полных квадратов
#define ERR_SQUARE 4

// Константа для проверки лежит ли позиция в интервале от 0 до размерв массива
#define ERR_ITER 5

//Константа вызывается если некоторое условие становится истинным
#define TRUE 1

//Константа вызывается если некоторое условие становится ложным
#define FALSE 0

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

/*Функция для провки числа: Является ли оно полным квадратом?.
Принимает один параметр - это само проверяемое число.
Возвращает TRUE если условие проверки верно, иначе вернёт FALSE.
*/
int check(int number)
{
    int k = FALSE;
    if (number == 1)
    {
        return TRUE;
    }
    for (int i = 1; i < number; i++)
    {
        if (number == i * i)
            k = TRUE;
    }
    return k;
}

/*Функция для сдвига элементов в массива. Принимает 3 элемента: массив, его размер и позииция сдвигаемого элемента. Ничего не возвращает*/
void rewrite(int *a, int i, int *n, int *rc)
{
	if (i >= 0 && i < *n)
	{	
		for (int j = i; j < *n; j++)
			a[j] = a[j + 1];
		(*n)--;
		(*rc) = OK;
	}
	else
		(*rc) = ERR_ITER;
}

/*Функция которая перебирает все элемты массива и если элемент удовлетворяет функцию check,
тогда вызывается функция rewrite, которая передвигает все элементы массива на одну позицию влево.
После перезаписи размер уменьшается на одну. Возвращает количество элементовв не являющихся полным квадратом.*/
int append(int *a, int n, int *rc)
{
    int i = 0, count = 0;
    while (i < n)
    {
        if (check(a[i]))
        {
            count++;
            rewrite(a, i, &n, rc);
            i--;
        }
        i++;
    }
    return count;
}

int main(void)
{
    int a[N_MAX];
    int n, rc = OK, s;
	setbuf(stdout, NULL);
    rc = array_input(a, &n);
    if (rc == OK)
    {
        if (n != 0)
        {
            s = append(a, n, &rc);
            if (s == n)
            {
                printf("All elements are full square");
                rc = ERR_SQUARE;
            }
            else
            {
                array_output(a, n - s);
            }
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
