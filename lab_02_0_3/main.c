#include <stdio.h>

#include <math.h>

//Эта константа возращает 1, то есть показывает нам что условие сравнения 2 вещественных чисел верно
#define TRUE 1

//Эта константа для сравнения вещественных чисел
#define EPS 1.0e-7

//Эта константа возращает 0, то есть показывает нам что условие  сравнения 2 вещественных чисел  неверно
#define FALSE 0

#define OK 0

// константа сообщает ошибку при вводе данных
#define ERR_IO 1 

// константа  сообщает нам, если значение точности больше единицы и меньше нуля
#define ERR_RANGE 2 

/* Эта функция создана для сравнения двух вещественных числа.
В аргументах принимает 2 значения: num_1 и num_2, и сравнивает их абсолютное значение
с константой EPS. Если условие выполняется, то возвращается 1, в противном случае 0.
*/

int compare(float num_1, float num_2)
{
    if (fabs(num_1 - num_2) < EPS)
        return TRUE;
    else
        return FALSE;
}

/*Эта функция предназначена для подсчёта суммы бесконечного ряда. 
Принимает два вещественных числа, то есть значене х и значение точности eps и возращает также вещественное число.
Возвращаемое значение является результатом выполненных действий, то есть вычисления суммы бесконечного ряда.
В переменной s в процессе выполнения функции хранится сумма ряда. В свою очередь в переменной t хранится
текущее значение бесконечного ряда. Сумма вычисляется до тех пор пока текущее значение не станет больше значения точности.
*/

float endless(float x, float eps)
{
    float s = 1, t = 1, k = 0;
    while (fabs(t) > eps)
    {
        k += 1;
        t *= x / k;
        s += t;
    }
    return s;
}

int main(void)
{
    float x, eps, f, absolute, regarding, rc = OK;
    setbuf(stdout, NULL);
    printf("Input all variables: ");
    if (scanf("%f%f", &x, &eps) == 2)
    {
        if (eps < 0 || eps > 1.0 || compare(eps, 0))
        {
            rc = ERR_RANGE;
            printf("Error in inputing\n");
        }
        else
        {
            printf("Approximate value of s(x) is %f\n", endless(x, eps));
            f = exp(x);
            printf("Exact value of f(x) is %f\n", f);
            absolute = fabs(f - endless(x, eps));
            regarding = fabs((f - endless(x, eps)) / f);
            printf("Absolute error is %f\n", absolute);
            printf("Relative error is %f\n", regarding);
        }
    }
    else
    {
        rc = ERR_IO;
        printf("Error\n");
    }
    return rc;
}
