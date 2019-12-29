#include <stdio.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define N_MAX 10

int input(int *a,int *n)
{
   printf("Input size of array: ");
   if (scanf("%d", n) != 1)
       return ERR_IO;
   if (*n <= 0 || *n > N_MAX)
       return ERR_RANGE;
   printf("Input elements: ");
   for (int i = 0; i < *n; i++)
       if (scanf("%d", &a[i]) != 1)
           return ERR_IO;
   return OK;
}

int check(int number)
{
    int count_3 = 0, end;
    if (number < 0)
        number = number * (-1);
    if (number >= 0 && number <= 9)
        return 0;
    while (number > 9)
    {
        end = number % 10;
        if (end == 3)
            count_3++;
        number = number / 10;
        if (number == 3)
            count_3++;
    }
    if (count_3 >= 2)
        return 1;
    else
        return 0;
}

void massiv (int *a, int n, int *size)
{
    *size = n;
    for (int i = 0; i < *size; i++)
    {
        if (check(a[i]))
        {
            *size += 1;
            for (int k = *size; k > i + 1; k--)
            {
                a[k] = a[k - 1];
            }
            a[i+1] = 0;
        }
        i++;
    }
}

void a_print(int *a, int n)
{
    printf("Array : ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main(void)
{
    int a[N_MAX], n, rc = OK, size;
    rc = input(a, &n);
    if (rc == OK)
    {
        massiv(a, n, &size);
        a_print(a, size);
    }
    return rc;
}
