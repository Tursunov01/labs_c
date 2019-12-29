#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_out.h"
#include "constants.h"
#include "structures.h"
#include "sort.h"

int main(int argc, char *argv[])
{
    int rc = OK;
    int len = 0, size;
    predmet_t **arr = NULL;
    FILE *f = NULL;
    setbuf(stdout, NULL);
    if (argc != 2 && argc != 3)
        rc = ERR_INPUT;
    if (rc == OK)
    {
        f = fopen(argv[1], "r");
        if (f)
        {
            fseek (f, 0, SEEK_END);
            size = ftell(f);
            if (size == 0)
                rc =  ERR_OPEN;
            if (rc == OK)
            {            
                fseek(f, 0, SEEK_SET);
                rc = read_file_and_count_strc(f, &len);
            }
            if (rc == OK && len != 0)
            {
                arr = malloc(len * sizeof(predmet_t*));
                if (!arr)
                    rc = ERR_ALLOCATED;
                if (rc == OK)
                {
                    rewind(f);
                    rc = read_file_and_add_arr(f, arr, len);
                }
            }
            fclose(f);
        }
        else
            rc = ERR_OPEN;
        if (argc == 3 && len != 0 && rc == OK)
        {
            if (strcmp(argv[2], "ALL") == 0)
                print_arr(arr, len);
            else
                find_substring(arr, len, argv[2]);
        }
        if (argc == 2 && len != 0 && rc == OK)
        {
            arr_sort(arr, len, cmp_density);
            print_arr(arr, len);
        }
    }
    if (len != 0)
        free_arr(arr, len);
    return rc;
}