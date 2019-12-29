#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "structure.h"
#include "operations.h"
#include "func.h"
#include "in_out.h"

int main(void)
{
    int rc = OK;
    char key[8];

    setbuf(stdout, NULL);
    
    //printf("Input key: ");
    if (!fgets(key, sizeof(key), stdin))
        rc = ERR_INPUT;
    if (rc == OK)
    {
        if (key[strlen(key) - 1] == '\n')
            key[strlen(key) - 1] = '\0';
        else
            rc = ERR_RANGE;
    }
    if (rc == OK)
        rc = choose_key(key);
    return rc;
}
