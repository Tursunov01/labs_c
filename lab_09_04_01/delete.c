#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include "constants.h"
#include "in_out.h"
#include"func.h"

/**
 * \fn make_matr_square(int64_t ***a, int *n, int *m)
 * \brief Функция, которая превращает введенную матрицу в квадратную.
 * \param [in] a - матрица
 * \param [in] n - количество строк
 * \param [in] m - количество столбцов
 * \return rc - код ошибки
 */

int make_matr_square(int64_t ***a, int *n, int *m)
{
    assert(*a);
    assert(*n > 0);
    assert(*m > 0);

    int p_c, p_r;
    int rc = OK;
    if (*n < *m)
    {
        while ((*n - *m) != 0)
        {
            find_pos_max(*a, *n, *m, &p_c, &p_r);
            move_left(*a, *n, *m, p_r);
            (*m)--;
            rc = resize_column(*a, *n, *m);
            if (rc != OK)
                return rc;
        }
    }
    else
    {
        while ((*n - *m) != 0)
        {
            find_pos_max(*a, *n, *m, &p_c, &p_r);
            free((*a)[p_c]);
            move_up(*a, *n, p_c);
            (*n)--;
            (*a)[*n] = NULL;
            rc = resize_row(a, *n);
            if (rc != OK)
                return rc;
        }
    }
    return rc;
}
