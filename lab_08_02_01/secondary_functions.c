#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "constants.h"

/**
 * \fn average(const double *parr, const double *pend)
 * \brief Функция для вычисления среднего арифметического массива.
 * \param [in] parr - указатель на начало массива
 * \param [in] pend - указатель на конец массива
 * \return sum - среднее арифметическое элементов массива
 */
double average(const double *parr, const double *pend)
{
    double sum = 0.0;
    const double *pcur;

    assert(parr != NULL);
    assert(pend != NULL);
    assert(parr < pend);

    pcur = parr;
    while (pcur < pend)
        sum += *pcur++;
    sum = sum / (pend - parr);
    return sum;
}

/**
 * \fn find_max(const double *parr, const double *pend)
 * \brief Функция для нахождения максимального элемента
 * \param [in] parr - указатель на начало массива
 * \param [in] pend - указатель на конец массива
 * \return max - максимальный элемент массива
 */
double find_max(const double *parr, const double *pend)
{
    const double *pcur;
    double max;

    assert(parr != NULL);
    assert(pend != NULL);
    assert(parr < pend);

    pcur = parr;
    max = *pcur;
    while (pcur < pend)
    {
        if (*pcur > max)
            max = *pcur;
        pcur++;
    }
    return max;
}

/**
 * \fn reallocate(double **parr, double **pend, int n)
 * \brief Функция для перевыделении памяти для массива.
 * \param [in] parr - указатель на указатель начала массива
 * \param [in] pend - указатель на указатель конца массива
 * \param [in] n - переменная в которой храниться количество элементов
 * \return rc - код ошибки
 */
int reallocate(double **parr, double **pend, int n)
{
    double *new = NULL;

    assert(*parr != NULL);
    assert(*pend != NULL);
    assert(n > 0);

    new = realloc(*parr, sizeof(double) * n);
    if (new)
    {
        *parr = new;
        *pend = (*parr + n);
        if (parr == pend)
            return ERR_ALLOCATION;
    }
    else
        return ERR_ALLOCATION;
    return OK;
}

/**
 * \fn move_left(double *pcur, double *pend)
 * \brief Функция для сдвига элементов влево на одну позицию.
 * \param [in] parr - указатель на начало массива
 * \param [in] pend - указатель на конец массива
 */
void move_left(double *pcur, double *pend)
{
    double *pnow;

    assert(pcur != NULL);
    assert(pend != NULL);

    pnow = pcur;
    while (pnow < pend - 1)
    {
        *pnow = *(pnow + 1);
        pnow++;
    }
}

/**
 * \fn move_right(double *pcur, double *pend)
 * \brief Функция для сдвига элементов вправо на одну позицию.
 * \param [in] parr - указатель на начало массива
 * \param [in] pend - указатель на конец массива
 */
void move_right(double *pcur, double *pend)
{
    double *pnow;

    assert(pcur != NULL);
    assert(pend != NULL);

    pnow = pend;
    while (pnow > pcur)
    {
        *pnow = *(pnow - 1);
        pnow--;
    }
}
