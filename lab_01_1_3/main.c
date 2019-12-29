#include <stdio.h>
int main(void)
{
    float v1, t1, v2, t2;
    float v, t;
    printf("Enter value and temperature of first capacity then the values of second: ");
    scanf("%f%f%f%f", &v1, &t1, &v2, &t2);
    v = v1 + v2;
    t = ((t1 * v1 + t2 * v2) / (v1 + v2));
    printf("\nThe summary value is ");
    printf("%.5f", v);
    printf("\n\nThe summary temperature of mixed water is ");
    printf("%.5f", t);
    return 0;
}
