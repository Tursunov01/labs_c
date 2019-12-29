#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "constants.h"

/**
 * \fn compare_float(const float a, const float b)
 * \brief Функция, которая сравнивает 2 вещественных числа.
 * \param [in] a - проверяемое вещественное число.
 * \param [in] b - проверяемое ещественное число.
 * \return - результат сравнения.
 */
int compare_float(const float a, const float b)
{
    if (fabs(a - b) < EPS)
        return 1;
    return 0;
}

/**
 * \fn compare_str(const char *a, const char *b)
 * \brief Функция, которая сравнивает 2 строки.
 * \param [in] a - проверямая строка.
 * \param [in] b - проверяемая строка.
 * \return - результат сравнения.
 */
int compare_str(const char *a, const char *b)
{
    for (int i = 0; i < strlen(b); i++)
    {
        if (b[i] != a[i])
            return 0;
    }
    return 1;
}

/**
 * \fn free_struct(predmet_t *cur)
 * \brief Функция, освобождающая память из под структуры.
 * \param [in] cur - структура
 */
void free_struct(predmet_t *cur)
{
    free(cur->name);
    free(cur);
}

/**
 * \fn free_arr(predmet_t **arr, int len)
 * \brief Функция, освобождающая память из под массива структур.
 * \param [in] arr - массив структур.
 * \param [in] len - длина массива.
 */
void free_arr(predmet_t **arr, int len)
{
   for (int i = 0; i < len; i++)
       free_struct(arr[i]);
   free(arr);
}

/**
 * \fn print_struct(predmet_t *cur)
 * \brief Функция, печатывающая структуру.
 * \param [in] cur - структура
 */

void print_struct(const predmet_t *cur)
{
    printf("%s\n", cur->name);
    printf("%f\n", cur->mass);
    printf("%f\n", cur->volume);
}

/**
 * \fn print_arr(predmet_t **arr, int len)
 * \brief Функция, печатывающая массив структур.
 * \param [in] arr - массив структур.
 * \param [in] len - длина массива.
 */
void print_arr(predmet_t **arr, int len)
{
   for (int i = 0; i < len; i++)
       print_struct(arr[i]);
}

/**
 * \fn allocate(const char *name, const float mass, const float volume)
 * \brief Функция, которая записывает входные данные в поля структуры 
 * \param [in] name - записываемое имя.
 * \param [in] mass - записываемая масса.
 * \param [in] volume - записываемый объём.
 * \return структуру.
 */
predmet_t* allocate(const char *name, const float mass, const float volume)
{
    predmet_t *cur = malloc(sizeof(predmet_t));
    if (!cur)
        return NULL;
    cur->name = malloc((strlen(name) + 1) * sizeof(char));
    if (!cur->name)
    {
        free_struct(cur);
        return NULL;
    }
    strcpy(cur->name, name);
    cur->mass = mass;
    cur->volume = volume;
    return cur;
}

/**
 * \fn input(FILE *f, char *name, float *mass, float *volume)
 * \brief Функция, которая считывает данные из файла и записывает эти данные в переменные. 
 * \param [in] name - записываемое имя.
 * \param [in] mass - записываемая масса.
 * \param [in] volume - записываемый объём.
 * \param [in] f - входной файл.
 * \return код ошибки.
 */
int input(FILE *f, char *name, float *mass, float *volume)
{
    char character[8];
    if (!fgets(name, MAX + 1, f))
        return ERR_INPUT;
    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = '\0';
    else
        return ERR_RANGE;
    if (strlen(name) == 0)
        return ERR_RANGE;
    if (fscanf(f, "%f", mass) != 1)
        return ERR_INPUT;
    if (*mass < 0 || compare_float(*mass, 0) == 1)
        return ERR_RANGE;
    if (fscanf(f, "%f", volume) != 1)
        return ERR_INPUT;
    if (*volume < 0 || compare_float(*volume, 0) == 1)
        return ERR_RANGE;
    fgets(character, sizeof(character), f);
    return OK;
}

/**
 * \fn read_file_and_count_strc(FILE *f, int *len)
 * \brief Функция, которая считывает данные из файла и считает количесво структур в переменную len. 
 * \param [in] f - входной файл.
 * \param [in] len - количество структур.
 * \return rc - код ошибки.
 */
int read_file_and_count_strc(FILE *f, int *len)
{
    char name[MAX + 1];
    float mass;
    float volume;
    int rc = OK;
    while (!feof(f) && rc == OK)
    {
        rc = input(f, name, &mass, &volume);
        if (rc == ERR_INPUT || rc == ERR_RANGE)
            (*len) = 0;
        if (rc == OK)
            (*len)++;
    }
    return rc;
}

/**
 * \fn read_file_and_add_arr(FILE *f, predmet_t **arr, int len)
 * \brief Функция, которая считывает данные из файла и записывает их в массив структур. 
 * \param [in] f - входной файл.
 * \param [in] arr - массив структур.
 * \return rc - код ошибки.
 */
int read_file_and_add_arr(FILE *f, predmet_t **arr, int len)
{
    predmet_t *cur = NULL;
    char name[MAX + 1];
    float mass;
    float volume;
    int i = 0;
    int rc = OK;
    while (!feof(f) && rc == OK)
    {
        rc = input(f, name, &mass, &volume);
        if (rc == OK)
        {
            cur = allocate(name, mass, volume);
            if (!cur)
                rc = ERR_ALLOCATED;
            if (rc == OK)
            {
                arr[i] = cur;
                i++;
            }
        }
    }
    if (i != len)
        return ERR_RANGE;
    return rc;
}

/**
 * \fn find_substring(predmet_t **arr, int len, char *substring)
 * \brief Функция, которая делает поиск в массиве структур по введенной подстроке. 
 * \param [in] len - длина массива.
 * \param [in] arr - массив структур.
 * \param [in] substring - подстрока.
 */
void find_substring(predmet_t **arr, int len, char *substring)
{
    for (int i = 0; i < len; i++)
    {
        if (compare_str(arr[i]->name, substring) == 1)
            print_struct(arr[i]);
    }
}