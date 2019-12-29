#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include "constants.h"

/**
 * \fn matrix_free(int64_t **a, int n)
 * \brief Функция, которая освобождает выделенную память под матрицу.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 */

void matrix_free(int64_t **a, int n)
{
    assert(a);
    assert(n > 0);

    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);
}

/**
 * \fn int64_t** matrix_alloc(int n, int m)
 * \brief Функция, которая инициализирует матрицу.
 * \param [in] m - количество столбцов
 * \param [in] n - количество строк
 * \return a - проинециализированную матрицу
 */

int64_t**matrix_alloc(int n, int m)
{
    assert(m > 0);
    assert(n > 0);

    int64_t **a = calloc(n, sizeof(int64_t*));
    if (!a)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        a[i] = malloc(m * sizeof(int64_t));
        if (!a[i])
        {
            matrix_free(a, n);
            return NULL;
        }
    }
    return a;
}

/**
 * \fn matrix_input(int64_t **a, int n, int m)
 * \brief Функция, которая вводит элементы матрицы.
 * \param [in] m - количество столбцов
 * \param [in] n - количество строк
 * \brief [in] a - матрица
 * \return rc - код ошибки
 */

int matrix_input(int64_t **a, int n, int m)
{
    assert(a);
    assert(n > 0);
    assert(m > 0);

    int rc = OK;
    printf("Input elements of matrix: ");
    for (int i = 0; rc == OK && i < n; i++)
    {
        for (int j = 0; rc == OK && j < m; j++)
        {
            if (scanf("%" PRId64, &a[i][j]) != 1)
                rc = ERR_INPUT;
        }
    }
    return rc;
}

/**
 * \fn matrix_create(int64_t ***a, int *n, int *m)
 * \brief Функция, которая создает матрицу.
 * \param [in] m - количество столбцов
 * \param [in] n - количество строк
 * \brief [in] a - матрица
 * \return rc - код ошибки
 */

int matrix_create(int64_t ***a, int *n, int *m)
{
    int64_t **ptr = NULL;
    int rc;
    printf("Input number of rows and columns: ");
    if (scanf("%d%d", n, m) != 2)
        return ERR_INPUT;
    if (*n <= 0 || *m <= 0)
        return ERR_RANGE;
    ptr = matrix_alloc(*n, *m);
    if (ptr == NULL)
        return ERR_MEM;
    rc = matrix_input(ptr, *n, *m);
    if (rc != OK)
    {
        matrix_free(ptr, *n);
        ptr = NULL;
    }
    *a = ptr;
    return rc;
}

/**
 * \fn matrix_print(int64_t **a, int n, int m)
 * \brief Функция, для печати матрицы.
 * \param [in] m - количество столбцов
 * \param [in] n - количество строк
 * \brief [in] a - матрица
 */

void matrix_print(int64_t **a, int n, int m)
{
    assert(a);
    assert(n > 0);
    assert(m > 0);

    printf("Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%"PRId64 " ", a[i][j]);
        printf("\n");
    }
}

/**
 * \fn input_powers(int *r, int *y)
 * \brief Функция, которая вводит степени для матриц.
 * \param [in] r - степень для первой матрицы
 * \param [in] y - степень для второй матрицы
 * \return rc - код ошибки
 */

int input_powers(int *r, int *y)
{
    printf("Input powers of r and y: ");
    if (scanf("%d%d", r, y) != 2)
        return ERR_INPUT;
    if (*r < 0 || *y < 0)
        return ERR_RANGE;
    return OK;
}
