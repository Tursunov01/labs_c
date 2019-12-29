#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "structures.h"
#include "in_out.h"

void free_struct(person_t *cur)
{
    free(cur->surname);
    free(cur);
}

void free_arr(person_t **arr, int len)
{
    for (int i = 0; i < len; i++)
       free_struct(arr[i]);
    free(arr);
}

void print_struct(person_t *cur)
{
    printf("%s\n", cur->surname);
    printf("%d\n", cur->year);
}

void print_arr(person_t **arr, int len)
{
    for (int i = 0; i < len; i++)
        print_struct(arr[i]);
}

person_t* allocate(const char *surname, int year)
{
    person_t *cur = malloc(sizeof(person_t));
    if (!cur)
        return NULL;
    cur->surname = malloc((strlen(surname) + 1) * sizeof(char));
    if (!cur->surname)
    {
        free_struct(cur);
        return NULL;
    }
    strcpy(cur->surname, surname);
    cur->year = year;
    return cur;
}

int read_file(FILE *f, char *surname, int *year)
{
    char buf[8];
    if (!fgets(surname, MAX + 1, f))
    {
        if (feof(f))
            return OK;
        return ERR_INPUT;
    }
    if (surname[strlen(surname) - 1] == '\n')
        surname[strlen(surname) - 1] = '\0';
    else
        return ERR_RANGE;
    if (strlen(surname) == 0)
        return ERR_RANGE;
    if (fscanf(f, "%d", year) != 1)
        return ERR_INPUT;
    if (*year <= 0)
        return ERR_RANGE;
    fgets(buf, sizeof(buf), f);
    return OK;
}


int count_len(FILE *f, int *len)
{
    char surname[MAX + 1];
    int year;
    int rc = OK;
    *len = 0;
    while (!feof(f))
    {
        rc = read_file(f, surname, &year);
        if (rc == OK)
            (*len)++;
        else
        {
            (*len) = 0;
            return rc;
        }
    }
    return rc;
}

int add_arr(FILE *f, person_t **arr, int len)
{
    int rc = OK;
    int i = 0;
    char surname[MAX + 1];
    int year;
    person_t *cur = NULL;
    while (!feof(f) && rc == OK)
    {
        rc = read_file(f, surname, &year);
        if (rc == OK)
        {
            cur = allocate(surname, year);
            if (!cur)
                rc = ERR_MEMORY;
            if (rc == OK)
            {
                arr[i] = cur;
                i++;
            }
        }
    }
    if (i != len)
        return ERR_RANGE;
    return OK;
}

int delete_equal(person_t **arr, int index, int *len)
{
    if (index < 0 || index >= (*len))
        return ERR_RANGE;
    free_struct(arr[index]);
    memmove(arr + index, arr + index + 1, (*len - index - 1) * sizeof(person_t*));
    (*len)--;
    return OK;
}

int check_struct(person_t **arr, int index, int len, person_t *cur, int *pos)
{
    for (int i = index; i < len; i++)
    {
        if (strcmp(arr[i]->surname, cur->surname) == 0 && arr[i]->year == cur->year)
        {
            (*pos) = i;
            return FIND;
        }
    }
    return NOT_FOUND;
}

int union_arr(person_t **res, person_t **a, person_t **b, int len1, int len2)
{
    person_t *cur = NULL;
    int rc = OK;
    int k = 0;
    for (int i = 0; i < len1 && rc == OK; i++)
    {
        cur = allocate(a[i]->surname, a[i]->year);
        if (!cur)
            rc = ERR_MEMORY;
        if (rc == OK)
        {
            res[k] = cur;
            k++;
        }
    }
    for (int i = 0; i < len2 && rc == OK; i++)
    {
        cur = allocate(b[i]->surname, b[i]->year);
        if (!cur)
            rc = ERR_MEMORY;
        if (rc == OK)
        {
            res[k] = cur;
            k++;
        }
    }
    return rc;
}