#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include "constants.h"
#include "delete.h"
#include "func.h"
#include "in_out.h"
#include "insert.h"
#include "multiply.h"

#define N_MAX 5

//функция для сравнения 2 матриц
int compare_matrix(int64_t **a, int64_t **b, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] != b[i][j])
                return 1;
        }
    }

    return 0;
}

//тесты для функции, которая находит максимальный элемент пробегаясь по столбцам
void test_find_pos_max(void)
{
    int errors = 0;
    {
        int c, r;
        int64_t **a = NULL;
        int n = 3, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4, a[0][1] = 7, a[0][2] = 6;
        a[1][0] = 3, a[1][1] = 2, a[1][2] = 9;
        a[2][0] = 1, a[2][1] = 7, a[2][2] = 5;

        find_pos_max(a, n, m, &c, &r);
        if (c != 1 && r != 2)
            errors++;
        matrix_free(a, n);
    }
    {
        int c, r;
        int64_t **a = NULL;
        int n = 4, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 0, a[0][1] = 2, a[0][2] = 1;
        a[1][0] = 1, a[1][1] = 2, a[1][2] = 2;
        a[2][0] = 3, a[2][1] = 3, a[2][2] = 3;
        a[3][0] = 8, a[3][1] = 8, a[3][2] = 2;

        find_pos_max(a, n, m, &c, &r);
        if (c != 3 && r != 1)
            errors++;
        matrix_free(a, n);
    }
    printf("Number of errors in function find_pos_max is %d/2\n", errors);
}


//тесты для функции, которая делает матрицу квадратной
void test_delete(void)
{
    int errors = 0;
    {
        int64_t b[][N_MAX] = { { 4, 7 }, { 3, 2 } };
        int64_t *ptrs[] = { b[0], b[1] };
        int64_t **a = NULL;
        int n = 2, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4;
        a[0][1] = 7;
        a[0][2] = 1;
        a[1][0] = 3;
        a[1][1] = 2;
        a[1][2] = 7;

        if (make_matr_square(&a, &n, &m) == OK)
        {
            if (compare_matrix(a, ptrs, n, m) == 1)
                errors++;
        }
        matrix_free(a, n);
    }
    {
        int64_t b[][N_MAX] = { { 1, 2, 2 }, { 3, 3, 3 }, { 8, 8, 2 } };
        int64_t *ptrs[] = { b[0], b[1], b[2] };
        int64_t **a = NULL;
        int n = 5, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 0, a[0][1] = 2, a[0][2] = 9;
        a[1][0] = 1, a[1][1] = 2, a[1][2] = 2;
        a[2][0] = 3, a[2][1] = 3, a[2][2] = 3;
        a[3][0] = 8, a[3][1] = 8, a[3][2] = 2;
        a[4][0] = 1, a[4][1] = 8, a[4][2] = 3;

        if (make_matr_square(&a, &n, &m) == OK)
        {
            if (compare_matrix(a, ptrs, n, m) == 1)
                errors++;
        }
        matrix_free(a, n);
    }
    printf("Number of errors in function delete is %d/2\n", errors);
}

//тесты для функции, которая перевыделяет заново память для строк матрицы
void test_resize_row(void)
{
    int errors = 0;
    {
        int64_t b[][N_MAX] = { { 4, 7 }, { 3, 2 } };
        int64_t *ptrs[] = { b[0], b[1] };
        int64_t **a = NULL;
        int n = 3, m = 2;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4, a[0][1] = 7;
        a[1][0] = 3, a[1][1] = 2;
        a[2][0] = 1, a[2][1] = 7;

        free(a[2]);
        if (resize_row(&a, n - 1) == OK)
        {
            if (compare_matrix(a, ptrs, n - 1, m) == 1)
                errors++;
        }
        matrix_free(a, n - 1);
    }
    {
        int64_t b[][N_MAX] = { { 0, 2, 9 }, { 1, 2, 2 }, { 3, 3, 3 }, { 8, 8, 2 } };
        int64_t *ptrs[] = { b[0], b[1], b[2], b[3] };
        int64_t **a = NULL;
        int n = 5, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 0, a[0][1] = 2, a[0][2] = 9;
        a[1][0] = 1, a[1][1] = 2, a[1][2] = 2;
        a[2][0] = 3, a[2][1] = 3, a[2][2] = 3;
        a[3][0] = 8, a[3][1] = 8, a[3][2] = 2;
        a[4][0] = 1, a[4][1] = 8, a[4][2] = 3;

        free(a[4]);
        if (resize_row(&a, n - 1) == OK)
        {
            if (compare_matrix(a, ptrs, n - 1, m) == 1)
                errors++;
        }
        matrix_free(a, n - 1);
    }
    printf("Number of errors in function resize_row is %d/2\n", errors);
}

//тесты для функции, которая перевыделяет память для столбцов матрицы
void test_resize_column(void)
{
    int errors = 0;
    {
        int64_t b[][N_MAX] = { { 4, 7 }, { 3, 2 }, { 1, 7 } };
        int64_t *ptrs[] = { b[0], b[1], b[2] };
        int64_t **a = NULL;
        int n = 3, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4, a[0][1] = 7, a[0][2] = 6;
        a[1][0] = 3, a[1][1] = 2, a[1][2] = 9;
        a[2][0] = 1, a[2][1] = 7, a[2][2] = 5;

        if (resize_column(a, n, m - 1) == OK)
        {
            if (compare_matrix(a, ptrs, n, m - 1) == 1)
                errors++;
        }
        matrix_free(a, n);
    }
    {
        int64_t b[][N_MAX] = { { 0, 2 }, { 1, 2 }, { 3, 3 }, { 8, 8 } };
        int64_t *ptrs[] = { b[0], b[1], b[2], b[3] };
        int64_t **a = NULL;
        int n = 4, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 0, a[0][1] = 2, a[0][2] = 9;
        a[1][0] = 1, a[1][1] = 2, a[1][2] = 2;
        a[2][0] = 3, a[2][1] = 3, a[2][2] = 3;
        a[3][0] = 8, a[3][1] = 8, a[3][2] = 2;

        if (resize_column(a, n, m - 1) == OK)
        {
            if (compare_matrix(a, ptrs, n, m - 1) == 1)
                errors++;
        }
        matrix_free(a, n);
    }
    printf("Number of errors in function resize_column is %d/2\n", errors);
}

//тесты для функции, которая сдвигает все столбцы матрицы на одну позицию влево
void test_move_left(void)
{
    int errors = 0;
    {
        int64_t b[][N_MAX] = { { 4, 6 }, { 3, 9 }, { 1, 5 } };
        int64_t *ptrs[] = { b[0], b[1], b[2] };
        int64_t **a = NULL;
        int n = 3, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4, a[0][1] = 7, a[0][2] = 6;
        a[1][0] = 3, a[1][1] = 2, a[1][2] = 9;
        a[2][0] = 1, a[2][1] = 7, a[2][2] = 5;

        move_left(a, n, m, 1);
        if (compare_matrix(a, ptrs, n, m - 1) == 1)
            errors++;
        matrix_free(a, n);
    }
    {
        int64_t b[][N_MAX] = { { 0, 2, 9, 7 }, { 6, 5, 3, 2 } };
        int64_t *ptrs[] = { b[0], b[1] };
        int64_t **a = NULL;
        int n = 2, m = 5;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 0, a[0][1] = 2, a[0][2] = 9, a[0][3] = 2, a[0][4] = 7;
        a[1][0] = 6, a[1][1] = 5, a[1][2] = 3, a[1][3] = 8, a[1][4] = 2;

        move_left(a, n, m, 3);
        if (compare_matrix(a, ptrs, n, m - 1) == 1)
            errors++;
        matrix_free(a, n);
    }
    printf("Number of errors in function move_left is %d/2\n", errors);
}

//тесты для фуекции, которая передвигает все строки матрицы на одну позицию вверх
void test_move_up(void)
{
    int errors = 0;
    {
        int64_t b[][N_MAX] = { { 4, 7 }, { 3, 2 }, { 6, 9 } };
        int64_t *ptrs[] = { b[0], b[1], b[2] };
        int64_t **a = NULL;
        int n = 4, m = 2;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4, a[0][1] = 7;
        a[1][0] = 3, a[1][1] = 2;
        a[2][0] = 1, a[2][1] = 7;
        a[3][0] = 6, a[3][1] = 9;

        free(a[2]);
        move_up(a, n, 2);
        a[n - 1] = NULL;
        if (compare_matrix(a, ptrs, n - 1, m) == 1)
            errors++;
        matrix_free(a, n);
    }
    {
        int64_t b[][N_MAX] = { { 1, 2 }, { 3, 3 }, { 8, 8 }, { 9, 2 }, { 3, 9 } };
        int64_t *ptrs[] = { b[0], b[1], b[2], b[3], b[4] };
        int64_t **a = NULL;
        int n = 6, m = 2;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 0, a[0][1] = 2;
        a[1][0] = 1, a[1][1] = 2;
        a[2][0] = 3, a[2][1] = 3;
        a[3][0] = 8, a[3][1] = 8;
        a[4][0] = 9, a[4][1] = 2;
        a[5][0] = 3, a[5][1] = 9;

        free(a[0]);
        move_up(a, n, 0);
        a[n - 1] = NULL;
        if (compare_matrix(a, ptrs, n - 1, m) == 1)
            errors++;
        matrix_free(a, n);
    }
    printf("Number of errors in function move_up is %d/2\n", errors);
}

//тесты для функции, которая считает среднее арифметическое столбцов
void test_average(void)
{
    int errors = 0;
    {
        int64_t **a = NULL;
        int n = 3, m = 3;
        a = matrix_alloc(n, m);
        assert(a);

        a[0][0] = 4, a[0][1] = 7, a[0][2] = 6;
        a[1][0] = 3, a[1][1] = 2, a[1][2] = 9;
        a[2][0] = 1, a[2][1] = 7, a[2][2] = 5;

        if (average(a, n, 0) != 2)
            errors++;
        if (average(a, n, 1) != 5)
            errors++;
        if (average(a, n, 2) != 6)
            errors++;
        matrix_free(a, n);
    }
    printf("Number of errors in function average is %d/3\n", errors);
}

//тесты для функции, которая находит минимальный элемент в строке матрицы
void test_find_min(void)
{
    int errors = 0;
    {
        int64_t **a = NULL;
        int n = 3, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4, a[0][1] = 7, a[0][2] = 6;
        a[1][0] = 3, a[1][1] = 2, a[1][2] = 9;
        a[2][0] = 1, a[2][1] = 7, a[2][2] = 5;

        if (find_min(a, m, 0) != 4)
            errors++;
        if (find_min(a, m, 1) != 2)
            errors++;
        if (find_min(a, m, 2) != 1)
            errors++;
        matrix_free(a, n);
    }
    printf("Number of errors in function find_min is %d/3\n", errors);
}

//тесты для функции, которая вставляет строку из средненго ариф. столбцов и столбец из мин. элемента строки
void test_insert(void)
{
    int errors = 0;
    {
        int64_t b[][N_MAX] = { { 4, 7, 4 }, { 3, 2, 2 }, { 3, 4, 3 } };
        int64_t *ptrs[] = { b[0], b[1], b[2] };
        int64_t **a = NULL;
        int n = 2, m = 2;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4, a[0][1] = 7;
        a[1][0] = 3, a[1][1] = 2;

        if (insert(&a, &n, &m, 1) == OK)
        {
            if (compare_matrix(a, ptrs, n, m) == 1)
                errors++;
        }
        matrix_free(a, n);
    }
    {
        int64_t b[][N_MAX] = { { 0, 2, 9, 0, 0 }, { 1, 2, 2, 1, 1 }, { 3, 3, 3, 3, 3 },
            { 8, 8, 2, 2, 2 }, { 3, 3, 4, 3, 3 }, { 3, 3, 4, 3, 3 } };
        int64_t *ptrs[] = { b[0], b[1], b[2], b[3], b[4], b[5] };
        int64_t **a = NULL;
        int n = 4, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 0, a[0][1] = 2, a[0][2] = 9;
        a[1][0] = 1, a[1][1] = 2, a[1][2] = 2;
        a[2][0] = 3, a[2][1] = 3, a[2][2] = 3;
        a[3][0] = 8, a[3][1] = 8, a[3][2] = 2;

        if (insert(&a, &n, &m, 2) == OK)
        {
            if (compare_matrix(a, ptrs, n, m) == 1)
                errors++;
        }
        matrix_free(a, n);
    }
    printf("Number of errors in function insert is %d/2\n", errors);
}


//тесты для функции, которая преобразует введенную матрицу в единичную
void test_single_matrix(void)
{
    int errors = 0;
    {
        int64_t b[][N_MAX] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
        int64_t *ptrs[] = { b[0], b[1], b[2] };
        int64_t **a = NULL;
        int n = 3, m = 3;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 4, a[0][1] = 7, a[0][2] = 6;
        a[1][0] = 3, a[1][1] = 2, a[1][2] = 9;
        a[2][0] = 1, a[2][1] = 7, a[2][2] = 5;

        single_matrix(a, n);
        if (compare_matrix(a, ptrs, n, m) == 1)
            errors++;
        matrix_free(a, n);
    }
    {
        int64_t b[][N_MAX] = { { 1, 0 }, { 0, 1 } };
        int64_t *ptrs[] = { b[0], b[1] };
        int64_t **a = NULL;
        int n = 2, m = 2;
        a = matrix_alloc(n, m);

        assert(a);

        a[0][0] = 0, a[0][1] = 2;
        a[1][0] = 1, a[1][1] = 3;

        single_matrix(a, n);
        if (compare_matrix(a, ptrs, n, m) == 1)
            errors++;
        matrix_free(a, n);
    }
    printf("Number of errors in function single_matrix is %d/2\n", errors);
}

//тесты для функции, которая перемножает две матрицы
void test_multiply(void)
{
    int errors = 0;
    {
        int64_t d[][N_MAX] = { { 23, 24, 12 }, { 36, 39, 21 }, { 48, 56, 44 } };
        int64_t *ptrs[] = { d[0], d[1], d[2] };
        int64_t **a = NULL, **b = NULL, **c = NULL;
        int n = 3, m = 3, p = 3, q = 3;
        a = matrix_alloc(n, m);
        b = matrix_alloc(n, m);
        c = matrix_alloc(n, m);

        assert(a);
        assert(b);
        assert(c);

        a[0][0] = 1, a[0][1] = 2, a[0][2] = 2;
        a[1][0] = 3, a[1][1] = 3, a[1][2] = 3;
        a[2][0] = 8, a[2][1] = 8, a[2][2] = 2;

        b[0][0] = 1, b[0][1] = 2, b[0][2] = 2;
        b[1][0] = 3, b[1][1] = 3, b[1][2] = 3;
        b[2][0] = 8, b[2][1] = 8, b[2][2] = 2;

        multiply(a, b, c, n, m, p, q);
        if (compare_matrix(c, ptrs, n, m) == 1)
            errors++;
        matrix_free(a, n);
        matrix_free(b, n);
        matrix_free(c, n);
    }
    {
        int64_t d[][N_MAX] = { { 4, 7, 4 }, { 3, 2, 2 }, { 3, 4, 3 } };
        int64_t *ptrs[] = { d[0], d[1], d[2] };
        int64_t **a = NULL, **b = NULL, **c = NULL;
        int n = 3, m = 3, p = 3, q = 3;
        a = matrix_alloc(n, m);
        b = matrix_alloc(n, m);
        c = matrix_alloc(n, m);

        assert(a);
        assert(b);
        assert(c);

        a[0][0] = 4, a[0][1] = 7, a[0][2] = 4;
        a[1][0] = 3, a[1][1] = 2, a[1][2] = 2;
        a[2][0] = 3, a[2][1] = 4, a[2][2] = 3;

        b[0][0] = 1, b[0][1] = 0, b[0][2] = 0;
        b[1][0] = 0, b[1][1] = 1, b[1][2] = 0;
        b[2][0] = 0, b[2][1] = 0, b[2][2] = 1;

        multiply(a, b, c, n, m, p, q);
        if (compare_matrix(c, ptrs, n, m) == 1)
            errors++;
        matrix_free(a, n);
        matrix_free(b, n);
        matrix_free(c, n);
    }
    printf("Number of errors in function multiply is %d/2\n", errors);
}

//тесты для функции, которая возводит матрицу в указанную степень
void test_exponentation(void)
{
    int errors = 0;
    {
        int64_t d[][N_MAX] = { { 496, 627, 438 }, { 261, 322, 228 }, { 342, 429, 301 } };
        int64_t *ptrs[] = { d[0], d[1], d[2] };
        int64_t **a = NULL, **c = NULL;
        int n = 3, m = 3;
        a = matrix_alloc(n, m);
        c = matrix_alloc(n, m);

        assert(a);
        assert(c);

        a[0][0] = 4, a[0][1] = 7, a[0][2] = 4;
        a[1][0] = 3, a[1][1] = 2, a[1][2] = 2;
        a[2][0] = 3, a[2][1] = 4, a[2][2] = 3;

        exponentation(a, c, 3, n);
        if (compare_matrix(c, ptrs, n, m) == 1)
            errors++;
        matrix_free(a, n);
        matrix_free(c, n);
    }
    {
        int64_t d[][N_MAX] = { { 23, 24, 12 }, { 36, 39, 21 }, { 48, 56, 44 } };
        int64_t *ptrs[] = { d[0], d[1], d[2] };
        int64_t **a = NULL, **c = NULL;
        int n = 3, m = 3;
        a = matrix_alloc(n, m);
        c = matrix_alloc(n, m);

        assert(a);
        assert(c);

        a[0][0] = 1, a[0][1] = 2, a[0][2] = 2;
        a[1][0] = 3, a[1][1] = 3, a[1][2] = 3;
        a[2][0] = 8, a[2][1] = 8, a[2][2] = 2;

        exponentation(a, c, 2, n);
        if (compare_matrix(c, ptrs, n, m) == 1)
            errors++;
        matrix_free(a, n);
        matrix_free(c, n);
    }
    printf("Number of errors in function exponentation is %d/2\n", errors);
}


int main(void)
{
    test_find_pos_max();
    test_delete();
    test_resize_row();
    test_resize_column();
    test_move_left();
    test_move_up();
    test_average();
    test_find_min();
    test_insert();
    test_single_matrix();
    test_multiply();
    test_exponentation();
    return 0;
}
