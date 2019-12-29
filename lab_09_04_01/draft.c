#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "constants.h"
#include "in_out.h"
#include "func.h"


int64_t avr(int64_t *a, int m)
{
    int64_t sum = 0;
    for (int i = 0; i < m; i++)
        sum += a[i];
    return sum;
}


void sortic(int64_t **a, int n, int m)
{
    int flag = 1, end = n - 1;
    int64_t *tmp = NULL;
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < end; i++)
        {
            if (avr(*(a + i), m) > avr(*(a + i + 1), m))
            {
                tmp = *(a + i);
                *(a + i) = *(a + i + 1);
                *(a + i + 1) = tmp;
            }
        }
        end--;
    }
}


int main(void)
{
    int64_t **a = NULL;
    int n, m;
    int rc;
    setbuf(stdout, NULL);
    rc = matrix_create(&a, &n, &m);
    if (rc == OK)
    {
        matrix_print(a, n, m);
        sortic(a, n, m);
        matrix_print(a, n, m);
    }
    matrix_free(a, n);
    return rc;
}
