#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "constants.h"
#include "in_out.h"
#include "func.h"
#include "delete.h"
#include "insert.h"
#include "multiply.h"

int main(void)
{
    int64_t **a = NULL, **b = NULL, **c = NULL;
    int n, m, p, q;
    int r, y;
    int rc;
    setbuf(stdout, NULL);
    rc = matrix_create(&a, &n, &m);
    if (rc == OK)
    {
        rc = matrix_create(&b, &p, &q);
        if (rc == OK)
        {
            rc = make_matr_square(&a, &n, &m);
            if (rc == OK)
            {
                rc = make_matr_square(&b, &p, &q);
                if (rc == OK)
                {
                    if (n > p)
                        rc = insert(&b, &p, &q, n - p);
                    else if (p > n)
                        rc = insert(&a, &n, &m, p - n);
                    else if (n == p)
                        rc = OK;
                    if (rc == OK)
                    {
                        rc = input_powers(&r, &y);
                        c = matrix_alloc(n, n);
                        if (rc == OK)
                        {
                            exponentation(a, c, r, n);
                            copy_array(a, c, n, n);
                            exponentation(b, c, y, n);
                            copy_array(b, c, n, n);
                            multiply(a, b, c, n, m, p, q);
                            matrix_print(c, n, m);
                            matrix_free(a, n);
                            matrix_free(b, n);
                            matrix_free(c, n);
                        }
                        else
                        {
                            matrix_free(a, n);
                            matrix_free(b, n);
                            matrix_free(c, n);
                        }
                    }
                    else
                    {
                        matrix_free(a, n);
                        matrix_free(b, p);
                    }
                }
                else
                {
                    matrix_free(a, n);
                    matrix_free(b, p);
                }
            }
            else
            {
                matrix_free(a, n);
                matrix_free(b, p);
            }
        }
        else
            matrix_free(a, n);
    }
    return rc;
}
