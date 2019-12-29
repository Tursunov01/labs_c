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

// Константа, которая вызывается если в массиве нет чисел начинаюцихся и заканчивающихся одной и той же цифрой
#define ERR_NUM 4

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
void array_output(const int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

/* Функция предназначена для сравнения первой цифры числа с последней, тем самым
если сравнение оказывается успешным, то возвращается единица, иначе нуль.
Принимает одно  целое значение - само число
 */
int compare(int number)
{
    int start, end;
    if (number < 0)
        number = (number) * -1;
    end = number % 10;
    if ((number / 10) != 0)
    {
        while (number > 9)
        {
            start = number / 10;
            number = number / 10;
        }
        if (start == end)
            return TRUE;
        else
            return FALSE;
    }
    return TRUE;
}

/*Функция для переписания элементов из массива а удовлетворяющих функцию compare,в массив new.
также для подсчета элементов неудовлетворяющих функцию compare.
В переменной n передаётся размер старого массива, а в переменной size перезаписывается размер нового массива new.
Также функция считает количество чисел начинающихся и заканчивающихся одним и тем же числом и возвращает это число
*/
int create(const int *a, int n, int *new)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (compare(a[i]))
        {
            new[j] = a[i];
            j++;
        }
    }
    return j;
}

int main(void)
{
    int a[N_MAX], new[N_MAX];
    int n, size, rc = OK;
    rc = array_input(a, &n);
    if (rc == OK)
    {
        if (n != 0)
        {    
            size = create(a, n, new);
            if (size != 0)
            {
                array_output(new, size);
            }
            else
            {
                printf("There is no number which starts and ends with same number");
                rc = ERR_NUM;
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
