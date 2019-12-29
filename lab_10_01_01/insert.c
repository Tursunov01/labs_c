#include <stdlib.h>
#include <assert.h>

#include "constants.h"
#include "structures.h"
#include "insert.h"

/**
 * \fn insert_grade(pupil_arr *arr)
 * \brief Функция, которая добавляет оценку 3 в массив оунок ученика.
 * \param [in] arr - массив записей
 * \return код ошибки
 */

int insert_grade(pupil_arr *arr)
{
    assert(arr);

    int num;
    for (int i = 0; i < arr->len; i++)
    {
        num = arr->data[i]->num_grades + 1;
        int *a = (int *) realloc(arr->data[i]->grades, sizeof(int) * (num));
        if (a)
        {
            arr->data[i]->grades = a;
            a = NULL;
        }
        else
            return ERR_MEMORY;
        arr->data[i]->grades[num - 1] = 3;
        arr->data[i]->num_grades = num;
    }
    return OK;
}
