#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include "constants.h"
#include "in_out.h"

/**
 * \fn find_pos_max(int64_t **a, int n, int m, int *p_c, int *p_r)
 * \brief Функция, которая находит позицию максимального элемента.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \param [in] m - количество столбцов
 * \param [in] p_c - позиция столбца
 * \param [in] p_r - позиция строки
 */

void find_pos_max(int64_t **a, int n, int m, int *p_c, int *p_r)
{
    assert(a);
    assert(n > 0);
    assert(m > 0);

    int64_t max = a[0][0];
    *p_c = 0;
    *p_r = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[j][i] >= max)
            {
                max = a[j][i];
                *p_c = j;
                *p_r = i;
            }
        }
    }
}

/**
 * \fn resize_row(int64_t ***a, int n)
 * \brief Функция, которая перевыделяет память для строк матрицы.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \return rc - код ошибки
 */

int resize_row(int64_t ***a, int n)
{
    assert(*a);
    assert(n > 0);

    int64_t **b = (int64_t**) realloc(*a, sizeof(int64_t*) * n);
    if (*b)
    {
        *a = b;
        b = NULL;
        return OK;
    }
    return ERR_ALLOCATION;
}

/**
 * \fn add_row(int64_t ***a, int n, int m)
 * \brief Функция, которая добавляет строку в матрицу.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \param [in] m - количество столбцов
 * \return rc - код ошибки
 */

int add_row(int64_t ***a, int n, int m)
{
    assert(*a);
    assert(n > 0);
    assert(m > 0);

    int rc = resize_row(a, n);
    if (rc == OK)
    {
        (*a)[n - 1] = malloc(m * sizeof(int64_t));
        if (!a)
        {
            matrix_free((*a), n);
            rc = ERR_ALLOCATION;
        }
    }
    return rc;
}

/**
 * \fn resize_column(int64_t **a, int n, int m)
 * \brief Функция, которая перевыделяет память для столбцов матрицы.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \param [in] m - количество столбцов
 * \return rc - код ошибки
 */

int resize_column(int64_t **a, int n, int m)
{
    assert(a);
    assert(n > 0);
    assert(m > 0);

    int rc;
    for (int i = 0; i < n; i++)
    {
        int64_t *b = (int64_t*) realloc(a[i], sizeof(int64_t) * m);
        {
            if (b)
            {
                a[i] = b;
                b = NULL;
                rc = OK;
            }
            else
                rc = ERR_ALLOCATION;
        }
    }
    return rc;
}

/**
 * \fn move_left(int64_t **a, int n, int m, int k)
 * \brief Функция, которая сдвигает все столбцы на одну позицию влево с указанной позиции.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \param [in] m - количество столбцов
 * \param [in] k - позиция с которой надо сдвинуть столбцы
 */

void move_left(int64_t **a, int n, int m, int k)
{
    assert(a);
    assert(n > 0);
    assert(m > 0);
    assert(k >= 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = k; j < m - 1; j++)
        {
            a[i][j] = a[i][j + 1];
        }
    }
}

/**
 * \fn move_up(int64_t **a, int n, int k)
 * \brief Функция, которая сдвигает все строки на одну позицию вверх с указанной позиции.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \param [in] k - позиция с которой надо сдвинуть столбцы
 */

void move_up(int64_t **a, int n, int k)
{
    assert(a);
    assert(n > 0);
    assert(k >= 0);

    for (int i = k; i < n - 1; i++)
        a[i] = a[i + 1];
}

/**
 * \fn average(int64_t **a, int n, int k, int64_t *res)
 * \brief Функция, которая считает среднее ариф. столбца.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \param [in] k - номер позиции столбца
 * \return sum - среднее арифметическое
 */

int64_t average(int64_t **a, int n, int k)
{
    assert(a);
    assert(n > 0);
    assert(k >= 0);

    int64_t sum = 0, cur;
    for (int i = 0; i < n; i++)
        sum = sum + a[i][k];
    cur = (sum / n) - 1;
    while (cur * n <= sum)
        cur++;
    return cur - 1;
}

/**
 * \fn find_min(int64_t **a, int m, int k)
 * \brief Функция, которая находит минимальный элемент в строке.
 * \param [in] a - матрица
 * \param [in] m - количество столбцов
 * \param [in] k - номер позиции строки
 * \return min - минимальный элемент
 */

int64_t find_min(int64_t **a, int m, int k)
{
    assert(a);
    assert(m > 0);
    assert(k >= 0);

    int64_t min = a[k][0];
    for (int i = 0; i < m; i++)
    {
        if (a[k][i] < min)
            min = a[k][i];
    }
    return min;
}

int copy_and_add(int64_t ***a, int *n, int m, const int64_t *arr, int n_row)
{
    (*n)++;
    int rc = resize_row(a, *n);
    if (rc == OK)
    {
        (*a)[n_row] = malloc(m * sizeof(int64_t));
        if (!a)
        {
            matrix_free((*a), (*n));
            rc = ERR_ALLOCATION;
        }
        else
        {
            for (int i = 0; i < m; i++)
                (*a)[n_row][i] = *(arr + i);
        }
    }
    return rc;
}
