#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "constants.h"
#include "structures.h"
#include "func.h"
#include "sort.h"

/**
 * \fn sort_by_birthday(const pupil *a, const pupil *b)
 * \brief Функция, компоратор для сравнения 2 записей по дате рождения.
 * \param [in] a - сравниваемая запись
 * \param [in] b - сравниваемая запись
 * \return признак, того надо ли поменять или нет
 */

bool sort_by_birthday(const pupil *a, const pupil *b)
{
    assert(a);
    assert(b);

    if (a->date.year > b->date.year)
        return false;
    if (a->date.year == b->date.year)
    {
        if (a->date.month > b->date.month)
            return false;
        if (a->date.month == b->date.month)
        {
            if (a->date.day > b->date.day)
                return false;
        }
    }
    return true;
}

/**
 * \fn sort_by_grade(const pupil *a, const pupil *b)
 * \brief Функция, компоратор для сравнения 2 записей по среднему арифметическому.
 * \param [in] a - сравниваемая запись
 * \param [in] b - сравниваемая запись
 * \return признак, того надо ли поменять или нет
 */

bool sort_by_grade(const pupil *a, const pupil *b)
{
    assert(a);
    assert(b);

    double sum1 = average(a->num_grades, a->grades);
    double sum2 = average(b->num_grades, b->grades);
    if (sum1 > sum2)
        return false;
    return true;
}

/**
 * \fn sort_by_sex(const pupil *a, const pupil *b)
 * \brief Функция, компоратор для сравнения 2 записей по полу.
 * \param [in] a - сравниваемая запись
 * \param [in] b - сравниваемая запись
 * \return признак, того надо ли поменять или нет
 */

bool sort_by_sex(const pupil *a, const pupil *b)
{
    assert(a);
    assert(b);

    int cur1 = (unsigned char) *a->sex;
    int cur2 = (unsigned char) *b->sex;
    cur1 = tolower(cur1);
    cur2 = tolower(cur2);
    if (cur1 == cur2)
        return true;
    return (cur1 < cur2);
//    if (strcmp(a->sex, b->sex) > 0)
//        return false;
//    return true;
}

/**
 * \fn sort_by_surname(const pupil *a, const pupil *b)
 * \brief Функция, компоратор для сравнения 2 записей по фамилии.
 * \param [in] a - сравниваемая запись
 * \param [in] b - сравниваемая запись
 * \return признак, того надо ли поменять или нет
 */

bool sort_by_surname(const pupil *a, const pupil *b)
{
    assert(a);
    assert(b);

    if (strcmp(a->surname, b->surname) > 0)
    {
        return false;
    }
    return true;
}

/**
 * \fn arr_sort(pupil_arr *arr, bool(*cmp)(const pupil *a, const pupil *b))
 * \brief Функция, которая сортирует массив записей по ключу.
 * \param [in] arr - массив записей
 * \param [in] cmp - ключ, по которому бедет осуществлена сортировка
 */

void arr_sort(pupil_arr *arr, bool(*cmp)(const pupil *a, const pupil *b))
{
    assert(arr);

    int min;
    //проход по всем элементам
    for (int i = 0; i < arr->len - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < arr->len; j++)
        {
            //условие проверки позиции сдвигаемого элемента
            if (cmp(arr->data[min], arr->data[j]) == false)
                min = j;
        }
        pupil *key = arr->data[min];
        //этот цикл позволяет устойчиво поменять местами элементы
        //здесь главное условие это min > i. i не даст поменяться местами элементы.
        while (min > i)
        {
            arr->data[min] = arr->data[min - 1];
            min--;
        }
        arr->data[i] = key;
    }
}
