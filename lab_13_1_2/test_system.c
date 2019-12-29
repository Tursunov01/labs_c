#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <dlfcn.h>

#include "cdio_lib.h"

#define EPS 10e-5

typedef int (*fn_delete_t)(double*, double**);
typedef int (*fn_reallocate_t)(double**, double**, int);
typedef double (*fn_find_max_t)(const double*, const double*);
typedef int (*fn_insert_t)(double**, double**, int, double);
typedef double (*fn_average_t)(const double*, const double*);
typedef void (*fn_move_left_t)(double*, double*);
typedef void (*fn_move_right_t)(double*, double*);

//Функция для сравнения 2 вещественных чисел
int compare_num(double a, double b)
{
    if (fabs(a - b) < EPS)
        return 1;
    return 0;
}

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
int test_average(void)
{
    void *hlib;
    int rc = OK;
    fn_average_t average;
    hlib = dlopen("./cdio.so", RTLD_LAZY);
    if (!hlib)
    {
        rc = ERR_ALLOCATION;
        return rc;
    }
    average = (fn_find_max_t) dlsym(hlib, "average");
    if (!average)
    {
        rc = ERR_ALLOCATION;
        dlclose(hlib);
        return rc;
    }
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
    if (hlib)
        dlclose(hlib);
    return rc;
}

//тесты для функции, находящую максимальный элемент в массиве
int test_findmax(void)
{
    
    void *hlib;
    int rc = OK;
    fn_find_max_t find_max;
    hlib = dlopen("./cdio.so", RTLD_LAZY);
    if (!hlib)
    {
        rc = ERR_ALLOCATION;
        return rc;
    }
    find_max = (fn_find_max_t) dlsym(hlib, "find_max");
    if (!find_max)
    {
        rc = ERR_ALLOCATION;
        dlclose(hlib);
        return rc;
    }
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
    if (!hlib)
        dlclose(hlib);
    return rc;
}

//тесты для функции, которая сдвигает все элементы на массива на 1 позицию влево
int test_move_left(void)
{
    void *hlib;
    int rc = OK;
    fn_move_left_t move_left;
    hlib = dlopen("./cdio.so", RTLD_LAZY);
    if (!hlib)
    {
        rc = ERR_ALLOCATION;
        return rc;
    }
    move_left = (fn_move_left_t) dlsym(hlib, "move_left");
    if (!move_left)
    {
        rc = ERR_ALLOCATION;
        dlclose(hlib);
        return rc;
    }
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
    if (!hlib)
        dlclose(hlib);
    return rc;
}

//тесты для функции, которая сдвигает все элементы на массива на 1 позицию вправо
int test_move_right(void)
{
    void *hlib;
    int rc = OK;
    fn_move_right_t move_right;
    hlib = dlopen("./cdio.so", RTLD_LAZY);
    if (!hlib)
    {
        rc = ERR_ALLOCATION;
        dlclose(hlib);
        return rc;
    }
    move_right = (fn_move_right_t) dlsym(hlib, "move_right");
    if (!move_right)
    {
        rc = ERR_ALLOCATION;
        dlclose(hlib);
        return rc;
    }
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
    if (!hlib)
        dlclose(hlib);
    return rc;
}

//тесты для функции, которая перевыделяет память массива
int test_reallocate(void)
{
    void *hlib;
    int rc = OK;
    fn_reallocate_t reallocate;
    hlib = dlopen("./cdio.so", RTLD_LAZY);
    if (!hlib)
    {
        rc = ERR_ALLOCATION;
        return rc;
    }
    reallocate = (fn_reallocate_t) dlsym(hlib, "reallocate");
    if (!reallocate)
    {
        rc = ERR_ALLOCATION;
        dlclose(hlib);
        return rc;
    }
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
    if (!hlib)
        dlclose(hlib);
    return rc;
}

//тесты для функции которая удаляет элементы массивы большие среднего арифметического массива
int test_delete(void)
{
    void *hlib;
    int rc = OK;
    fn_delete_t delete;
    hlib = dlopen("./cdio.so", RTLD_LAZY);
    if (!hlib)
    {
        rc = ERR_ALLOCATION;
        return rc;
    }
    delete = (fn_delete_t) dlsym(hlib, "delete");
    if (!delete)
    {
        rc = ERR_ALLOCATION;
        dlclose(hlib);
        return rc;
    }
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
    if (!hlib)
        dlclose(hlib);
    return rc;
}

//тесты для функции которая вставляет максимальный элемент на позицию, также в начало и конец массива
int test_insert(void)
{
    void *hlib;
    int rc = OK;
    fn_insert_t insert;
    hlib = dlopen("./cdio.so", RTLD_LAZY);
    if (!hlib)
    {
        rc = ERR_ALLOCATION;
        return rc;
    }
    insert = (fn_insert_t) dlsym(hlib, "insert");
    if (!insert)
    {
        rc = ERR_ALLOCATION;
        dlclose(hlib);
        return rc;
    }
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
    if (!hlib)
        dlclose(hlib);
    return rc;
}

int main(void)
{
    
    int rc = OK;
    setbuf(stdout, NULL);
    rc = test_average();
    if (rc != OK)
        return rc;
    rc = test_findmax();
    if (rc != OK)
        return rc;
    rc = test_move_left();
    if (rc != OK)
        return rc;
    rc = test_move_right();
    if (rc != OK)
        return rc;
    rc = test_reallocate();
    if (rc != OK)
        return rc;
    rc = test_delete();
    if (rc != OK)
        return rc;
    rc = test_insert();
    if (rc != OK)
        return rc;
    return rc;
}
