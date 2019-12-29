#include <stdio.h>
#include <math.h>
#define  PI  3.1415926535897932384626433832795 //число пи
int main(void)
{
    float a, b, alpha, s;
    printf("Enter all parametrs of trapezium: \n");
    scanf("%f%f%f", &a, &b, &alpha);
    s = fabs((a * a - b * b)) / 4 * tan(alpha * PI / 180);
    printf("The square of trapezium is ");
    printf("%.5f", s);
    return 0;
}
