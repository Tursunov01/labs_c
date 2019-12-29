#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

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
