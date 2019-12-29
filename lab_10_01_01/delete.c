#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "arr_struct.h"
#include "constants.h"
#include "structures.h"
#include "func.h"
#include "delete.h"

/**
 * \fn delete_girls(pupil_arr *arr)
 * \brief Функция, которая удаляет всех девушек больше 17 лет из массива записей.
 * \param [in] arr - массив записей
 * \return rc - код ошибки
 */

int delete_girls(pupil_arr *arr, const char *sex, int age)
{
    assert(arr);

    int i = 0;
    int rc = OK;
    while (rc == OK && i < arr->len)
    {
        if (cmp_case_insentive(arr->data[i]->sex, sex) == 0)
        {
            if (check_age(arr->data[i], age) == OK)
            {
                rc = arr_delete(arr, i);
                i--;
            }
        }
        i++;
    }
    return rc;
}
