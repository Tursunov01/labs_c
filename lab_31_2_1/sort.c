#include "structures.h"
#include <stdio.h>

/**
 * \fn cmp_density(const predmet_t *curl, const predmet_t *curr)
 * \brief Функция, которая сравнивает 2 плотности.
 * \param [in] curl - проверяемая структура.
 * \param [in] curr - проверяемая структура.
 * \return - результат сравнения.
 */
int cmp_density(const predmet_t *curl, const predmet_t *curr)
{
    float den1 = curl->mass/curl->volume;
    float den2 = curr->mass/curr->volume;

    if (den1 > den2)
        return 1;
    return 0;
}

/**
 * \fn arr_sort(predmet_t **arr, int len, int (*cmp)(predmet_t *curl, predmet_t *curr))
 * \brief Функция, которая сортирует по плотности.
 * \param [in] arr - массив структур.
 * \param [in] len - чество структур в массиве.
 * \param [in] cmp - функция компаратор
 * \return - результат сравнения.
 */
void arr_sort(predmet_t **arr, int len, int (*cmp)(predmet_t *curl, predmet_t *curr))
{
    int min;
    for (int i = 0; i < len - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < len; j++)
        {
            if (cmp(arr[min], arr[j]) == 1)
                min = j;
        }
        if (min != i)
        {
            predmet_t *tmp = arr[min];
            arr[min] = arr[i];
            arr[i] = tmp;
        }
    }
}
