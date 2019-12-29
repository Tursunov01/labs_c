#include <stdio.h>
#define NUMBER_OF_FLATS 36  //число квартир в одном подъезде
#define NUMBER_FLAT_ON_FLOOR  4 // количество квартир на одном этаже
int main(void)
{
    int n, p, e;
    printf("Enter the number of flat: ");
    scanf("%d", &n);
    p = ((n - 1) / NUMBER_OF_FLATS + 1);
    e = ((n - (p - 1) * NUMBER_OF_FLATS) - 1) / NUMBER_FLAT_ON_FLOOR + 1;
    printf("Number of entrance is ");
    printf("%d", p);
    printf("\nNumber of floor is ");
    printf("%d", e);
    return 0;
}
