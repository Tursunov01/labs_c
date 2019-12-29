#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//#include "cdio_lib.h"

typedef int (*fn_input_t)(double**, double**, int*);
typedef int (*fn_delete_t)(double*, double**);
typedef int (*fn_reallocate_t)(double**, double**, int);
typedef double (*fn_find_max_t)(const double*, const double*);
typedef int (*fn_insert_t)(double**, double**, int, double);
typedef void (*fn_print_t)(const double*, const double*);
typedef void (*fn_print_errors_t)(int);

int main(void)
{
    void *hlib;
    double *a = NULL;
    double *end = NULL;
    double m2;
    int n, rc = 0, p;

    setbuf(stdout, NULL);

    fn_input_t input;
    fn_delete_t delete;
    fn_reallocate_t reallocate;
    fn_find_max_t find_max;
    fn_insert_t insert;
    fn_print_t print;
    fn_print_errors_t print_errors;

    hlib = dlopen("./cdio.so", RTLD_LAZY);
    if (!hlib)
    {
        rc = -4;
        return rc;
    }
    input = (fn_input_t) dlsym(hlib, "input");
    if (!input)
    {
        rc = -4;
        dlclose(hlib);
        return rc;
    }
    delete = (fn_delete_t) dlsym(hlib, "delete");
    if (!delete)
    {
        rc = -4;
        dlclose(hlib);
        return rc;
    }
    reallocate = (fn_reallocate_t) dlsym(hlib, "reallocate");
    if (!reallocate)
    {
        rc = -4;
        dlclose(hlib);
        return rc;
    }
    find_max = (fn_find_max_t) dlsym(hlib, "find_max");
    if (!find_max)
    {
        rc = -4;
        dlclose(hlib);
        return rc;
    }
    insert = (fn_insert_t) dlsym(hlib, "insert");
    if (!insert)
    {
        rc = -4;
        dlclose(hlib);
        return rc;
    }
    print = (fn_print_t) dlsym(hlib, "print");
    if (!print)
    {
        rc = -4;
        dlclose(hlib);
        return rc;
    }
    print_errors = (fn_print_errors_t) dlsym(hlib, "print_errors");
    if (!print_errors)
    {
        rc = -4;
        dlclose(hlib);
        return rc;
    }
    rc = input(&a, &end, &n);//проверка на успешный ввод
    if (rc == 0)
    {
        rc = delete(a, &end);//проверка на успешное удаление
        if (rc == 0)
        {
            rc = reallocate(&a, &end, end - a);
            if (rc == 0)
            {
                printf("Input p: "); //ввод позиции
                if (scanf("%d", &p) != 1)
                    rc = -3;
                if (rc == 0)
                {
                    if (p > n || p < 0)
                        rc = -3;
                    if (rc == 0)
                    {
                        //printf("end - a is %I64d\tp + 1 is %d\n", end - a, p + 1);
                        if (end - a < p + 1)
                            rc = -3;
                        else
                        {
                            m2 = find_max(a, end);
                            rc = insert(&a, &end, p, m2);
                            if (rc == 0)
                            {
                                if (insert(&a, &end, 0, m2) == 0)
                                {
                                    rc = insert(&a, &end, end - a, m2);
                                    if (rc == 0)
                                        print(a, end);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    free(a);
    if (!hlib)
        dlclose(hlib);
    print_errors(rc);
    return rc;
}
