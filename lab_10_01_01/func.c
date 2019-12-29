#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "constants.h"
#include "structures.h"
#include "in_out.h"
#include "sort.h"
#include "func.h"

/**
 * \fn cmp_case_insentive(const char *a, const char *b)
 * \brief Функция, которая сравнивает 2 строки.
 * \param [in] a - сравнимаемая строка
 * \param [in] b - сравнимаемая строка
 * \return разница кодов отличившихся символов
 */

int cmp_case_insentive(const char *a, const char *b)
{
    int cur1 = (unsigned char) *a;
    int cur2 = (unsigned char) *b;
    cur1 = tolower(cur1);
    cur2 = tolower(cur2);
    while (cur1 == cur2 && cur1 != '\0')
    {
        a++;
        b++;
        cur1 = tolower(*a);
        cur2 = tolower(*b);
    }
    return cur1 - cur2;
}

/**
 * \fn check_leap_year(int year)
 * \brief Функция, которая проверяет год на високосный.
 * \param [in] year - год рождения
 * \return Результат проверки
 */

int check_leap_year(int year)
{
    if (year % 400 == 0)
        return OK;
    else if (year % 100 == 0)
        return ERR_RANGE;
    else if (year % 4 == 0)
        return OK;
    return ERR_RANGE;
}

/**
 * \fn valid_date(int year, int month, int day)
 * \brief Функция, которая проверяет валидность даты рождения ученика.
 * \param [in] year - год рождения
 * \param [in] month - месяц рождения
 * \param [in] day - день рождения
 * \return код ошибки
 */

int valid_date(birthdate *cur)
{
    if (cur->year < 0 || cur->year >= 2019)
        return ERR_INPUT;
    if (check_leap_year(cur->year) == OK)
    {
        if (cur->month == 2 && cur->day > 29)
            return ERR_INPUT;
    }
    else
    {
        if (cur->month == 2 && cur->day > 28)
            return ERR_INPUT;
    }
    if (cur->month < 1 || cur->month > 12)
        return ERR_INPUT;
    if (cur->month == 1 || cur->month == 3 || cur->month == 5 ||
        cur->month == 7 || cur->month == 8 || cur->month == 10 || cur->month == 12)
    {
        if (cur->day < 1 || cur->day > 31)
            return ERR_INPUT;
    }
    if (cur->month == 4 || cur->month == 6 || cur->month == 9 || cur->month == 11)
    {
        if (cur->day < 1 || cur->day > 30)
            return ERR_INPUT;
    }
    return OK;
}

/**
 * \fn check_birthday(const char *birthday)
 * \brief Функция, которая проверяет дату рождения ученика.
 * \param [in] birthday - день рождение ученика в виде строки
 * \return rc - код ошибки
 */

int check_birthday(const char *birthday, birthdate *date)
{
    int rc;
    if (strlen(birthday) != 10)
        return ERR_INPUT;
    for (int i = 0; i < strlen(birthday); i++)
    {
        if (isdigit(birthday[i]) == 0 && birthday[i] != '.')
            return ERR_INPUT;
    }
    if (birthday[4] != '.' && birthday[7] != '.')
        return ERR_INPUT;
    date->year = atoi(birthday);
    date->month = atoi(birthday + 5);
    date->day = atoi(birthday + 8);
    rc = valid_date(date);
    return rc;
}

/**
 * \fn check_age(pupil *kids)
 * \brief Функция, которая проверяет возраст ученика. Дата отсчёта 01.11.2019
 * \param [in] kids - запись об ученике
 * \return - код, показывающий является ли возраст старше 17 или нет
 */

int check_age(const pupil *kids, int age)
{
    //условие проверки на возраст. Условие становится верным, если возраст равен или больше 17
    if (2019 - kids->date.year >= age)
    {
        /*проверка граничного года рождения. То есть если год рождения равен 2002.
        То потенциально его возраст старше 17, если не учитывать месяц и день.
        Поэтому проверка идет на эти случаи. То есть если год рожения старше 2002.11.01, то ему еще нет 17.*/
        if (kids->date.year == 2002 && kids->date.month >= 11 && kids->date.day > 1)
            return LESS_AGE;
        return OK;
    }
    return LESS_AGE;
}

/**
 * \fn average(const pupil *kids)
 * \brief Функция, которая считает среднее арифметическое оценок за последнюю четверть
 * \param [in] n - количество оценок
 * \param [in] grades - массив оценок
 * \return - среднее арифметическое
 */

double average(int n, int *grades)
{
    assert(grades);
    assert(n > 0);

    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += grades[i];
    sum /= n;
    return sum;
}

/**
 * \fn sort_with_key(pupil_arr *arr)
 * \brief Функция, которая сортирую массив записей по введенному ключу
 * \param [in] arr - массив записей
 * \return - код ошибки
 */

int sort_with_key(pupil_arr *arr)
{
    char key[MAX_LEN];
    printf("Input key of sort: ");
    if (!fgets(key, sizeof(key), stdin))
        return ERR_INPUT;
    if (key[strlen(key) - 1] == '\n')
        key[strlen(key) - 1] = '\0';
    if (strcmp(key, "SEX") == 0)
    {
        arr_sort(arr, sort_by_sex);
        return OK;
    }
    if (strcmp(key, "SURNAME") == 0)
    {
        arr_sort(arr, sort_by_surname);
        return OK;
    }
    if (strcmp(key, "GRADE") == 0)
    {
        arr_sort(arr, sort_by_grade);
        return OK;
    }
    if (strcmp(key, "BIRTHDATE") == 0)
    {
        arr_sort(arr, sort_by_birthday);
        return OK;
    }
    return ERR_INPUT;
}

/**
 * \fn check_surname(char *surname)
 * \brief Функция, которая проверяет введенную фамилию на буквы латинского алфавита
 * \param [in] surname - проверяемая строка
 * \return - код ошибки
 */

int check_surname(const char *surname)
{
    for (int i = 0; i < strlen(surname); i++)
    {
        if (isalpha(surname[i]) == 0)
            return ERR_INPUT;
    }
    return OK;
}
