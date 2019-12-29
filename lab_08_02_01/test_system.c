#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "constants.h"
#include "secondary_functions.h"
#include "forming_new_array.h"
#define EPS 10e-5

//Функция для сравнения 2 вещественных чисел
int compare_num(double a, double b)
{
    if (fabs(a - b) < EPS)
        return 1;
    return 0;
}

//Функция для сравнеия 2 вещественных массивов
//int compare_arr(const double *a, const double *b, int size)
//{
//    for (int i = 0; i < size; i++)
//    {
//        if (compare_num(a[i], b[i]) == 0)
//            return 0;
//    }
//    return 1;
//}

int compare_arr(const double *pcur1, const double *pcur2, const double *pend1, const double *pend2)
{
    if (pend1 - pcur1 != pend2 - pcur2)
        return 0;
    while (pcur1 < pend1 && pcur2 < pend2)
    {
        if (compare_num(*pcur1, *pcur2) == 0)
            return 0;
        pcur1++;
        pcur2++;
    }
    return 1;
}

//тесты для функции вычисления среднего арифметического массива
void test_average(void)
{
    int count = 0;
    {
        double a[] = { 1, 2, -2.2, -0.1, 6 };
        if (compare_num(average(a, a + 5), 1.34) == 0)
            count++;
    }
    {
        double a[] = { 1, 2, 3, 4, 5, 6, 1.2 };
        if (compare_num(average(a, a + 7), 3.171428) == 0)
            count++;
    }
    printf("Module tests for function average:\nIncorreect %d/2\n", count);
}

//тесты для функции, находящую максимальный элемент в массиве
void test_findmax(void)
{
    int count = 0;
    {
        //максимальный элемент в конце
        double a[] = { 1, 2, -2.2, -0.1, 6 };
        if (compare_num(find_max(a, a + 5), 6) == 0)
            count++;
    }
    {
        //максимальный элемент в начале
        double a[] = { 10, 2, 3, 4, 5, 6, 1.2 };
        if (compare_num(find_max(a, a + 7), 10) == 0)
            count++;
    }
    {
        //максимальных элементов 2
        double a[] = { -1, 2, 3, -7, -5, 8, 6, 1.2 };
        if (compare_num(find_max(a, a + 8), 8) == 0)
            count++;
    }
    printf("Module tests for function findmax:\nIncorreect %d/3\n", count);
}

//тесты для функции, которая сдвигает все элементы на массива на 1 позицию влево
void test_move_left(void)
{
    int count = 0;
    {
        double a[] = { 1, 2, 3, 4, 5 };
        double b[] = { 2, 3, 4, 5 };
        move_left(a, a + 5);
        if (compare_arr(a, b, a + 4, b + 4) == 0)
            count++;
    }
    {
        double a[] = { 1, -4, -3, 2.2, 7, -1.37 };
        double b[] = { 1, -3, 2.2, 7, -1.37 };
        move_left(a + 1, a + 6);
        if (compare_arr(a, b, a + 5, b + 5) == 0)
            count++;
    }
    printf("Module tests for function move_left:\nIncorreect %d/2\n", count);
}

//тесты для функции, которая сдвигает все элементы на массива на 1 позицию вправо
void test_move_right(void)
{
    int count = 0;
    {
        double a[6] = { -1, 2, 3, 4, 5 };
        double b[5] = { -1 ,-1, 2, 3, 4 };
        move_right(a, a + 5);
        if (compare_arr(a, b, a + 5, b + 5) == 0)
            count++;
    }
    {
        double a[6] = { 1, -4, -3, 4, 5 };
        double b[5] = { 1, 1, -4, -3, 4 };
        move_right(a, a + 5);
        if (compare_arr(a, b, a + 5, b + 5) == 0)
            count++;
    }
    printf("Module tests for function move_right:\nIncorreect %d/2\n", count);
}

//тесты для функции, которая перевыделяет память массива
void test_reallocate(void)
{
    int count = 0;
    {
        //случай когда размер перевыделенного массива меньше чем начальное n
        double *a = NULL, *end = NULL;
        int n = 5;
        a = calloc(n, sizeof(double));
        end = a + 4;
        if (reallocate(&a, &end, 3) != 0)
            count++;
        free(a);
    }
    {
        //случай когда размер перевыделенного массива больше чем начальное n
        double *a = NULL, *end = NULL;
        int n = 5;
        a = calloc(n, sizeof(double));
        end = a + 4;
        if (reallocate(&a, &end, 7) != 0)
            count++;
        free(a);
    }
    {
        //случай когда размер перевыделенного массива равное начальному n
        double *a = NULL, *end = NULL;
        int n = 5;
        a = calloc(n, sizeof(double));
        end = a + 4;
        if (reallocate(&a, &end, 5) != 0)
            count++;
        free(a);
    }
    printf("Module tests for function reallocate:\nIncorreect %d/3\n", count);
}

//тесты для функции которая удаляет элементы массивы большие среднего арифметического массива
void test_delete(void)
{
    int count = 0;
    {
        double a[] = { 1, 2, 3 };
        double b[] = { 1, 2 };
        double *cur2 = a + 3;
        if (delete(a, &cur2) == 0)
        {
            if (compare_arr(a, b, a + 2, b + 2) == 0)
                count++;
        }
    }
    {
        double a[] = { 1, 2, 3, 4, 5, 6, 1.2 };
        double b[] = { 1, 2, 3, 1.2 };
        double *cur2 = a + 7;
        if (delete(a, &cur2) == 0)
        {
            if (compare_arr(a, b, a + 4, b + 4) == 0)
                count++;
        }
    }
    printf("Module tests for function delete:\nIncorreect %d/2\n", count);
}

//тесты для функции которая вставляет максимальный элемент на позицию, также в начало и конец массива
void test_insert(void)
{
    int count = 0;
    {
        double *a = malloc(3 * sizeof(double));
        double *end = a + 3;
        double b[] = { 2, 1, 2 };

        assert(a);

        a[0] = 1;
        a[1] = 2;
        a[2] = 0;

        if (insert(&a, &end, 0, 2) == OK)
        {
            if (compare_arr(a, b, end - 1, b + 3) == 0)
                count++;
        }
        free(a);
    }
    {
        double *a = malloc(5 * sizeof(double));
        double *end = a + 5;
        double b[] = { 1, 2, 3, 3, 1.2 };

        assert(a);

        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        a[3] = 1.2;
        a[4] = 0;

        if (insert(&a, &end, 3, 3) == OK)
        {
            if (compare_arr(a, b, end - 1, b + 5) == 0)
                count++;
        }
        free(a);
    }
    printf("Module tests for function insert:\nIncorreect %d/2\n", count);
}

int main(void)
{
    test_average();
    test_findmax();
    test_move_left();
    test_move_right();
    test_reallocate();
    test_delete();
    test_insert();
    return 0;
}
