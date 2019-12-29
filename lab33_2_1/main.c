#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "structures.h"
#include "in_out.h"

int main(int argc, char *argv[])
{
    int rc = OK;
    person_t **arr1 = NULL, **arr2 = NULL, **arr3 = NULL;
    int len1 = 0, len2 = 0, len3 = 0, pos = 0, size = 0, flag = 0;
    FILE *f = NULL;
    setbuf(stdout, NULL);
    if (argc != 3)
        rc = ERR_INPUT;
    if (rc == OK)
    {
        f = fopen(argv[1], "r");
        if (!f)
            rc = ERR_OPEN;
        if (rc == OK)
        {
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            if (size != 0)
            {
                rewind(f);    
                rc = count_len(f, &len1);
                if (rc == OK && len1 != 0)
                {
                    arr1 = malloc(len1 * sizeof(person_t*));
                    if (!arr1)
                        rc  = ERR_MEMORY;
                    if (rc == OK)
                    {
                        rewind(f);
                        rc = add_arr(f, arr1, len1);
                    }
                }
            }
            else
                flag++;
            fclose(f);
        }
    }
    if (rc == OK)
    {
        f = fopen(argv[2], "r");
        if (!f)
            rc = ERR_OPEN;
        if (rc == OK)
        {
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            if (size != 0)
            {
                rewind(f);
                rc = count_len(f, &len2);
                if (rc == OK && len2 != 0)
                {
                    arr2 = malloc(len2 * sizeof(person_t*));
                    if (!arr2)
                        rc  = ERR_MEMORY;
                    if (rc == OK)
                    {
                        rewind(f);
                        rc = add_arr(f, arr2, len2);
                    }
                }
            }
            else
                flag++;
            fclose(f);
        }
    }
        
    if (flag == 2)
        rc = EMPTY;
    if (rc == OK)
    {
        len3 = len1 + len2;
        arr3 = malloc(len3 * sizeof(person_t*));
        if (!arr3)
            rc = ERR_MEMORY;
        if (rc == OK)
        {
            rc = union_arr(arr3, arr1, arr2, len1, len2);
            int i = 0;
            while (i < len3 && rc == OK)
            {
                if (check_struct(arr3, i + 1, len3, arr3[i], &pos) == FIND)
                {
                    rc = delete_equal(arr3, pos, &len3);
                    i = -1;
                }
                i++;
            }
            if (rc == OK)
            {
                person_t **tmp = realloc(arr3, len3 * sizeof(person_t*));
                if (tmp)
                {
                    arr3 = tmp;
                    tmp = NULL;
                }
                else
                    rc = ERR_MEMORY;
                if (rc == OK)
                    print_arr(arr3, len3);
            }
        }
    }
    if (len1 != 0 && arr1 != NULL)
        free_arr(arr1, len1);
    if (len2 != 0 && arr2 != NULL)
        free_arr(arr2, len2);
    if (len3 != 0 && arr3 != NULL) 
        free_arr(arr3, len3);
    return rc;
}
