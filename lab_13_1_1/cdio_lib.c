#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cdio_lib.h"

int input_elements(double *pcur, double *pend)
{
    printf("Input elements: ");
    while (pcur < pend)
    {
        if (scanf("%lf", pcur++) != 1)
            return ERR_INPUT;
    }
    return OK;
}

/**
 * \fn input(double **parr, double **pend, int *n, int *p)
 * \brief Функция ввода количества элементов и элементов массива.
 * \param [in] parr - указатель на указатель начала массива
 * \param [in] pend - указатель на указатель конца массива
 * \param [in] n - переменная в которую запишется количество элементов
 * \return rc - код ошибки
 */

int input(double **parr, double **pend, int *n)
{
    double *a = NULL;
    double *pcur;
    printf("Input n: ");
    if (scanf("%d", n) != 1)
        return ERR_SIZE;
    if (*n <= 0)
        return ERR_RANGE;
    a = malloc(*n * sizeof(double));
    if (a == NULL)
        return ERR_ALLOCATION;
    pcur = a;
    *pend = (a + *n);
    if (input_elements(pcur, *pend) != OK)
    {
        free(a);
        return ERR_INPUT;
    }
    *parr = a;
    a = NULL;
    return OK;
}

/**
 * \fn print(double *parr, const double *pend)
 * \brief Функция вывода массива.
 * \param [in] parr - указатель на начало массива
 * \param [in] pend - указатель на  конец массива
 */

void print(const double *parr, const double *pend)
{
    const double *pcur = parr;
    printf("Array:\n");
    while (pcur < pend)
        printf("%lf ", *pcur++);
    printf("\n");
}

/**
 * \fn print_errors(int rc)
 * \brief Функция для печати ошибок.
 * \param [in] rc - переменная содержащая код ошибки
 */

void print_errors(int rc)
{
    if (rc == ERR_INPUT)
        printf("Error in input.\n");
    else if (rc == ERR_RANGE)
        printf("Error in size of array.\n");
    else if (rc == ERR_ALLOCATION)
        printf("Error! Can not creat array.\n");
    else if (rc == EMPTY_ARRAY)
        printf("Error! Array is empty\nn");
    else if (rc == ERR_LEN)
        printf("Error! Position of insert is nor correct\n");
}

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