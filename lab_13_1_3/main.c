#include <stdio.h>
#include <stdlib.h>

#include "cdio_lib.h"

int main(void)
{
    double *a = NULL;
    double *end = NULL;
    double m2;
    int n, rc = OK, p;
    setbuf(stdout, NULL);
    rc = input(&a, &end, &n);//проверка на успешный ввод
    if (rc == OK)
    {
        rc = delete(a, &end);//проверка на успешное удаление
        if (rc == OK)
        {
            rc = reallocate(&a, &end, end - a);
            if (rc == OK)
            {
                printf("Input p: "); //ввод позиции
                if (scanf("%d", &p) != 1)
                    rc = ERR_LEN;
                if (rc == OK)
                {
                    if (p > n || p < 0)
                        rc = ERR_LEN;
                    if (rc == OK)
                    {
                        //printf("end - a is %I64d\tp + 1 is %d\n", end - a, p + 1);
                        if (end - a < p + 1)
                            rc = ERR_LEN;
                        else
                        {
                            m2 = find_max(a, end);
                            rc = insert(&a, &end, p, m2);
                            if (rc == OK)
                            {
                                if (insert(&a, &end, 0, m2) == OK)
                                {
                                    rc = insert(&a, &end, end - a, m2);
                                    if (rc == OK)
                                        print(a, end);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    arr_free(a);
    print_errors(rc);
    return rc;
}
