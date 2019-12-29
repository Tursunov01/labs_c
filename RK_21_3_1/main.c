#include <stdio.h>

int solve (int number)
{
    int  check = 0, maxx = 0, minn = 9, end;
    if (number < 0)
        number = number *(-1);
    if (number == 0)
        check = 0;
    else
    {
        while (number > 0)
        {
            end = number % 10;
            if (end <= minn)
            {
                minn = end;
                check = 0;
            }
            if (end >= maxx)
            {
                maxx = end;
                check = 1;
            }
            number = number / 10;
        }
    }
    return check;
}


int main (void)
{
    int number, rc;
    printf("Input number: ");
    if (scanf("%d", &number) == 1)
    {
        if (solve(number) == 0)
            printf("min max");
        else if (solve(number) == 1)
                printf("max min");
        rc = 0;
    }
    else
    {
        printf("Error input\n");
        rc = 1;
    }
    return rc;
}
