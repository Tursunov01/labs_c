#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include "constants.h"
#include "func.h"
#include "in_out.h"

/**
 * \fn insert(int64_t ***a, int *n, int *m, int k)
 * \brief Функция, которая вставляет строку из сред. ариф. столбца и столбец из мин. элемента строки.
 * \param [in] a - матрица
 * \param [in] m - количество столбцов
 * \param [in] n - количество строк
 * \param [in] k - количество вставок
 * \return rc - код ошибки
 */

int insert(int64_t ***a, int *n, int *m, int k)
{
    assert(*a);
    assert(*n > 0);
    assert(*m > 0);
    assert(k >= 0);

    int rc;
    int k1 = k, k2 = k;
    int64_t min, sum;
//    while (k1 > 0)
//    {
//        (*n)++;
//        rc = add_row(a, *n, *m);
//        k--;
//        if (rc == OK)
//        {
//            for (int i = 0; i < *m; i++)
//            {
//                sum = average((*a), (*n) - 1, i);
//                (*a)[(*n) - 1][i] = sum;
//            }
//            k1--;
//        }
//        else
//            return rc;
//    }
    while (k1 > 0)
    {
        int64_t *arr = malloc((*m) * sizeof(int64_t));
        if (arr == NULL)
            return ERR_ALLOCATION;
        for (int i = 0; i < (*m); i++)
        {
            sum = average((*a), (*n), i);
            *(arr + i) = sum;
        }
        rc = copy_and_add(a, n, *m, arr, *n);
        if (rc != OK)
            return rc;
        k1--;
        free(arr);
    }
    while (k2 > 0)
    {
        (*m)++;
        rc = resize_column(*a, *n, *m);
        if (rc == OK)
        {
            for (int i = 0; i < *n; i++)
            {
                min = find_min(*a, (*m) - 1, i);
                (*a)[i][(*m) - 1] = min;
            }
            k2--;
        }
        else
            return rc;
    }
    return rc;
}
