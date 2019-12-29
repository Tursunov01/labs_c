#include <stdio.h>
#include <assert.h>
#include "constants.h"
#include "secondary_functions.h"
#include"input_output.h"

/**
 * \fn delete(double *parr, double **pend)
 * \brief Функция для удаления элементов большего среднего арифметического массива.
 * \param [in] parr - указатель на начало массива
 * \param [in] pend - указатель на указатель конца массива
 * \return rc - код ошибки
 */

int delete(double *parr, double **pend)
{
    double m1 = average(parr, *pend);
    double *pcur = parr, *end = *pend;
    int rc = OK;

    assert(parr != NULL);
    assert(pend != NULL);

    while (pcur < end)
    {
        if (*pcur > m1)
        {
            move_left(pcur, end);
            end--;
            pcur--;
        }
        pcur++;
    }
    *pend = end;
    if (end - parr == 0)
        return EMPTY_ARRAY;
    return rc;
}



/**
 * \fn insert(double **parr, double **pend, int p, double m2)
 * \brief Функция для встаки максимального элемента на введенную пользователем позицию.
 * Также максимальный элемент вставиться в начало и конец массива
 * \param [in] parr - указатель на указатель начала массива
 * \param [in] pend - указатель на указатель конца массива
 * \param [in] p - позиция вставки элемента
 * \param [in] m2 - переменная в которой храниться максимальный элемент
 * \return rc - код ошибки
 */

//int insert(double *parr, double *pend, int p, double m2)
//{
//    double *start, *end, *pos;
//    int rc = OK;

//    assert(parr != NULL);
//    assert(pend != NULL);
//    assert(p >= 0 && p < (pend - parr));

//    pos = parr + p;
//    start = parr;
//    end = pend - 3;
//    while (start < end)
//    {
//        if (start == pos)
//        {
//            move_right(start, end);
//            *start = m2;
//            end = pend - 2;
//            start = parr;
//            move_right(start, end);
//            end = pend - 1;
//            *parr = m2;
//            *end = m2;
//            break;
//        }
//        else
//            start++;
//    }
//    return rc;
//}

//int insert(double **parr, double **pend, int p, double m2)
//{
//    double *start, *pos, *end;
//    int rc;
//    rc = reallocate(parr, pend, *pend - *parr + 1);
//    if (rc == OK)
//    {
//        start = *parr;
//        end = *pend - 1;
//        pos = *parr + p;
//        while (start <= end)
//        {
//            if (start == pos)
//            {
//                move_right(start, end);
//                *start = m2;
//                break;
//            }
//            start++;
//        }
//    }
//    return rc;
//}


int insert(double **parr, double **pend, int p, double m2)
{
    double *pos, *end;
    int rc;
    rc = reallocate(parr, pend, *pend - *parr + 1);
    if (rc == OK)
    {
        end = *pend - 1;
        pos = *parr + p;
        move_right(pos, end);
        *pos = m2;
    }
    return rc;
}
