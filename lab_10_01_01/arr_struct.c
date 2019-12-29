#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "constants.h"
#include "structures.h"
#include "in_out.h"
#include "arr_struct.h"

/**
 * \fn arr_init(pupil_arr *arr)
 * \brief Функция, которая массив записей, и их количетво.
 * \param [in] arr - массив записей
 */

void arr_init(pupil_arr *arr)
{
    arr->data = NULL;
    arr->len = 0;
    arr->allocated = 0;
}

/**
 * \fn arr_append(pupil_arr *arr, pupil *current)
 * \brief Функция, которая добавляет запись в массив записей.
 * \param [in] arr - массив записей
 * \param [in] current - добавляемая запись
 * \return код ошибки
 */

int arr_append(pupil_arr *arr, pupil *current)
{
    if (!arr->data)
    {
        arr->data = malloc(INIT_SIZE * sizeof(pupil *));
        if (!arr->data)
            return ERR_MEMORY;
        arr->allocated = INIT_SIZE;
    }
    else
    {
        if (arr->len >= arr->allocated)
        {
            pupil **tmp = realloc(arr->data, arr->allocated * STEP * sizeof(pupil *));
            if (!tmp)
                return ERR_MEMORY;
            arr->data = tmp;
            arr->allocated *= STEP;
        }
    }
    arr->data[arr->len] = current;
    arr->len++;
    return OK;
}

/**
 * \fn arr_print(FILE *f, const pupil_arr *arr)
 * \brief Функция, которая  записывает массив записей в файл.
 * \param [in] arr - массив записей
 * \param [in] f - файловая переменная
 */

void arr_print(FILE *f, const pupil_arr *arr)
{
    for (int i = 0; i < arr->len; i++)
        pupil_print(f, arr->data[i]);
}

/**
 * \fn arr_free(pupil_arr *arr)
 * \brief Функция, которая освобождает память из под массива записей.
 * \param [in] arr - массив записей
 */

void arr_free(pupil_arr *arr)
{
    for (int i = 0; i < arr->len; i++)
        pupil_free(arr->data[i]);
    if (arr->data)
        free(arr->data);
    arr_init(arr);
}

/**
 * \fn arr_delete(pupil_arr *arr, int index)
 * \brief Функция, которая удаляет запись по индексу из массива записей
 * \param [in] arr - массивей записей
 * \param [in] index - позиция удаляемой записи
 * \return - код ошибки
 */

int arr_delete(pupil_arr *arr, int index)
{
    assert(arr);

    if (index < 0 || index >= arr->len)
        return ERR_RANGE;
    pupil_free(arr->data[index]);
    memmove(arr->data + index, arr->data + index + 1, (arr->len - index - 1) * sizeof(pupil*));
    arr->len--;
    return OK;
}
