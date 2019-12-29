#include <stdio.h>
#include <string.h>

// Константа для максимального размера строки
#define MAX_LEN 256

/*Аналог функции strlen. Вычисляет длину строки*/
int my_strlen(const char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

/*Функция аналог функции strrchr. Ищет последнее входжения символа в строке.
Принимает строку и код символа. При успешном выполнении вернет указатель на этот символ иначе NULL.*/

const char *my_strrchr(const char *str, const int c)
{
    const char *result = NULL;
    for (int i = my_strlen(str); i >= 0; i--)
    {
        if (str[i] == c)
        {
            result = &str[i];
            return result;
        }
    }
    return result;
}

/*Функция аналог функции strcspn, которая определяет начальную длину строки не содержащей символы подстроки.
Возвращает эту позицию, принимает строкуи подстроку.
В главном цикле функции берется символ из out и проверяется со всеми символами из in.
Счетчик count увеличивается до тех пор пока не найдет совпадение между символами.
Если в in не находится символ, то получаем следующий символ из out и повторяем этиже действия.*/

int my_strcspn(const char *in, const char *out)
{
    int j = 0, i = 0, count = 0, minn = my_strlen(in);
    while (out[i] != '\0')
    {
        count = 0;
        j = 0;
        while (in[j] != '\0')
        {
            if (in[j] != out[i])
                count++;
            else
            {
                if (count <= minn && count >= 0)
                    minn = count;
            }
            j++;
        }
        i++;
    }
    return minn;
}

/*Тесты для функции my_strrchr. Возвращает количество неудачных тестов*/
int test_my_strrchr(void)
{
    int errors = 0;
    char str[MAX_LEN+1] = "";
    if (my_strrchr(str, '\0') != strrchr(str, '\0'))
        errors++;
    if (my_strrchr(str, 'z') != strrchr(str, 'z'))
        errors++;
    if (my_strrchr(str, 'a') != strrchr(str, 'a'))
        errors++;
    return errors;
}

/*Тесты для функции my_strcspn. Возвращает количество неудачных тестов*/
int test_my_strcspn(void)
{
    int errors = 0;
    char str[MAX_LEN+1] = "hello i am hello you i am";
    if (my_strcspn(str, "hello") != strcspn(str, "hello"))
        errors++;
    if (my_strcspn(str, "w") != strcspn(str, "w"))
        errors++;
    if (my_strcspn(str, "i am") != strcspn(str, "i am"))
        errors++;
    return errors;
}

int main(void)
{
    int result;
    result = test_my_strcspn();
    printf("number of errors of test_my_strcspn is %d/3\n", result);
    result = test_my_strrchr();
    printf("number of errors  of test_my_strrchr is %d/3\n", result);
    return 0;
}
