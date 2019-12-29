#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "structures.h"
#include "cdio.h"

int main(int argc, char *argv[])
{
    struct node_t *list = NULL, *result = NULL;
    int rc = OK;
    FILE *f = NULL;
    float sred;
    int n = 0, size = 0;
    setbuf(stdout, NULL);
    if (argc != 2)
        rc = ERR_INPUT;
    if (rc == OK)
    {
        f = fopen(argv[1], "r");
        if (!f)
            rc = ERR_INPUT;
        if (rc == OK)
        {
            fseek (f, 0, SEEK_END);
            size = ftell(f);
            if (size == 0)
                rc =  ERR_INPUT;
            if (rc == OK)
            {
                rewind(f);
                list = read_file(f);
                sred = srednee(list, &n);
                sred = sred / n;
                result = oper_del(list, sred);
                list_print(result);
            }
            fclose(f);
        }
    }
    list_free(list);
    list_free(result);
    return rc;
}
