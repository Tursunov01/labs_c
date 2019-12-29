#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "constants.h"
#include "structures.h"
#include "in_out.h"
#include "arr_struct.h"
#include "delete.h"
#include "insert.h"
#include "sort.h"
#include "func.h"

int main(void)
{
    FILE *f = NULL;
    pupil_arr arr;
    pupil *current = NULL;
    int rc;
    setbuf(stdout, NULL);
    arr_init(&arr);
    printf("Input pupil info. To stop enter input \"nobody\"\n");
    do
    {
        rc = pupil_input(&current);
        if (rc == OK)
            rc = arr_append(&arr, current);
    }
    while (rc == OK);
    if (rc == ERR_STOP)
    {
        if (arr.len != 0)
        {
            rc = delete_girls(&arr, "female", 17);
            if (rc == OK)
            {
                if (arr.len != 0)
                {
                    rc = insert_grade(&arr);
                    if (rc == OK)
                    {
                        rc = sort_with_key(&arr);
                        if (rc != ERR_INPUT)
                        {
                            f = fopen("kids.txt", "w");
                            if (f)
                            {
                                arr_print(f, &arr);
                                fclose(f);
                            }
                            else
                                rc = ERR_INPUT;
                        }
                    }
                }
                else
                    rc = ERR_RANGE;
            }
        }
        else
            rc = ERR_RANGE;
    }
    arr_free(&arr);
    return rc;
}
