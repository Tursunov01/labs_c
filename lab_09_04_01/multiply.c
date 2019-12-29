#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include "in_out.h"
#include "constants.h"

/**
 * \fn single_matrix(int64_t **a, int n)
 * \brief Функция, которая преобразует введенную матрицу в единичную.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 */

void single_matrix(int64_t **a, int n)
{
    assert(a);
    assert(n > 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                a[i][i] = 1;
            else
                a[i][j] = 0;
        }
    }
}

/**
 * \fn copy_array(int64_t **x, int64_t **a, int n)
 * \brief Функция, которая копирует элементы одной матрицы и вставляет её в другую матрицу.
 * \param [in] x - вставляемая матрица
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \param [in] m - количество столбцов
 */

void copy_array(int64_t **x, int64_t **a, int n, int m)
{
    assert(a);
    assert(x);
    assert(n > 0);
    assert(m > 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            x[i][j] = a[i][j];
    }
}

/**
 * \fn multiply(int64_t **a, int64_t **b, int64_t **c, int n, int m)
 * \brief Функция, которая умножает две матрицы и записывае её в третью.
 * \param [in] a - умножаемая матрица
 * \param [in] b - умножаемая матрица
 * \param [in] c - матрица - результат
 * \param [in] m - количество столбцов
 * \param [in] n - количество строк
 */

void multiply(int64_t **a, int64_t **b, int64_t **c, int n, int m, int p, int q)
{
    assert(a);
    assert(b);
    assert(c);
    assert(n > 0);
    assert(m > 0);
    assert(p > 0);
    assert(q > 0);
    assert(m == p && n == q);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
}

/**
 * \fn exponentation(int64_t **a, int64_t **c, int power, int n
 * \brief Функция, которая возводит введенную матрицу в степень.
 * \param [in] a - матрица
 * \param [in] c - матрица - результат
 * \param [in] n - количество строк
 * \param [in] power - степень возведения
 */

void exponentation(int64_t **a, int64_t **c, int power, int n)
{
    assert(a);
    assert(c);
    assert(power >= 0);
    assert(n > 0);

    int64_t **x = NULL;
    x = matrix_alloc(n, n);
    copy_array(x, a, n, n);
    if (power == 0)
    {
        single_matrix(x, n);
        copy_array(c, x, n, n);
    }
    else if (power == 1)
        copy_array(c, x, n, n);
    else
    {
        for (int i = 1; i < power; i++)
        {
            multiply(a, x, c, n, n, n, n);
            copy_array(x, c, n, n);
        }
    }
    matrix_free(x, n);
}
