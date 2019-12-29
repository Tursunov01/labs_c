#include <stdio.h>

#define OK 0

// Ошибка ввода числа через функцию scanf
#define ERR_IO 1

// Проверка показателя степени
#define ERR_RANGE 2       

// Будет считаться ошибкой , когда число будет представлено в виде 0^0
#define ERR_POW 3         

/* Эта функция принимает 2 целых числа и предназначена для возведения числа в степень,
указанную в аргументах функции. Эта функция возводит в степень превый аргумент, то есть a,
в степень второго аргумента n и в итоге возращает целое число result, 
которое является результатом всех действий
*/

int power(int a, int n)
{
    int result = 1;
    while (n > 0)
    {
        result *= a;
        n -= 1;
    }
    return result;
}

int main(void)
{
    int a, n, rc = OK;
    setbuf(stdout, NULL);
    printf("Input number and his power ");
    if (scanf("%d%d", &a, &n) == 2)
    {
        if (n < 0)
        {
            rc = ERR_RANGE;
            printf("The exponent must be greater than zero\n ");
        }
        else if (n == 0)
        {
            rc = ERR_POW;
            printf("Exponent can not be zero");
        }
        else
        {
            printf("Your result is %d", power(a, n));
        }
    }
    else
    {
        rc = ERR_IO;
        printf("Error\n");
    }
    return rc;
}
