#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

#include "constants.h"
#include "func.h"

/**
 * \fn int_to_arr(int n, int *arr, int key)
 * \brief Функция, переводящее десятичное число в введенную сис. счисления. Результат записывает в массив чисел.
 * \param [in] n - число которое нужно перевести.
 * \param [in] arr - массив в котором будет записан результат.
 * \param [in] key - Система счисления в которую надо перевести.
 * \return i - размер массива.
 */


int int_to_arr(int *arr, unsigned int n, int key)
{
    int i = 0;
    while (n > key - 1)
    {
        arr[i] = (n % key);
        n /= key;
        i++;
    }
    arr[i] = n;
    return i + 1;
}
/**
 * \fn my_strlen(char *str)
 * \brief Функция считающая длину строки. Аналог функции strlen.
 * \param [in] str - Строка, длину которую надо измерить.
 * \return i - размер строки.
 */

int my_strlen(const char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void my_strcat(char *str, char cur)
{
    int len = my_strlen(str);
    str[len] = cur;
    str[len + 1] = '\0';
}



/**
 * \fn int check_sym(const char *str, int i)
 * \brief Функция, для проверки спецификатора.
 * \param [in] str - вся строка.
 * \param [in] i - позиция спецификатора.
 * \return - возвращает специальную константу, показывающую какой спецификатор был найден.
 */

int check_sym(const char *str, int i)
{
    if (str[i] == '%')
    {
        if (str[i + 1] == 'd')
            return INT;
        else if (str[i + 1] == 's')
            return STR;
        else if (str[i + 1] == '%')
            return PER;
        else if (str[i + 1] == 'h')
        {
            if (str[i + 2] == 'o')
                return OCT;
        }
    }
    return NOT_FOUND;
}

/**
 * \fn my_snprintf(const char *buf, int n, const char *str, ...)
 * \brief Функция с переменным числом параметров. Аналог функции snprintf. 
 * \brief Записывает в buf n количество символов из str.
 * \param [in] buf - строка в которую будет записан результат.
 * \param [in] n - количество символов которое нужно записать.
 * \param [in] str - введенная строка
 * \return - размер строки str.
 */

int my_snprintf(char *buf, int n, const char *str, ...)
{
    int i = 0, flag;
    int d, len, sum = 0;
    unsigned int ho;
    const char *cur, *res;
    int arr[MAX_INT];
    va_list argptr;
    va_start(argptr, str);
    cur = str;
    if (buf != NULL)
        buf[0] = '\0';
    while (cur[i] != '\0')
    {
        flag = check_sym(cur, i);
        if (flag == NOT_FOUND)
        {
            if (n >= 0 && sum < n - 1)
                my_strcat(buf, cur[i]);
            sum++;
        }
        if (flag == PER)
        {
            if (n >= 0 && sum < n - 1)
                my_strcat(buf, cur[i + 1]);
            sum++;
            i++;
        }
        else if (flag == INT)
        {
            d = va_arg(argptr, int);
            if (d < 0)
            {
                if (n >= 0 && sum < n - 1)
                    my_strcat(buf, '-');
                sum++;
                unsigned int tmp = (unsigned int) (d * (-1));
                len = int_to_arr(arr, tmp, 10);
            }
            else
                len = int_to_arr(arr, d, 10);
            for (int j = len - 1; j >= 0; j--)
            {
                if (n >= 0 && sum < n - 1)
                    my_strcat(buf, arr[j] + '0');
                sum++;
            }
            i++;
        }   
        else if (flag == STR)
        {
            res = va_arg(argptr, char*);
            for (int j = 0; j < my_strlen(res); j++)
            {
                if (n >= 0 && sum < n - 1)
                    my_strcat(buf, res[j]);
                sum++;
            }
            i++;
        }
        else if (flag == OCT)
        {
            ho = va_arg(argptr, int);
            len = int_to_arr(arr, ho, 8);
            for (int j = len - 1 ; j >= 0; j--)
            {
                if (n >= 0 && sum < n - 1)
                    my_strcat(buf, arr[j] + '0');
                sum++;
            }
            i = i + 2;
        } 
        i++;
    }
    va_end(argptr);
    return sum;
}
