#include <stdio.h>
#define PI 3.14
float rectangle(float a, float b)
{
    return a * b;
}
float circle(float r)
{
    return PI * r * r;
}
int main(void)
{
    float sr,a,b,r,sc,s;
    printf("Input a and b and r: ");
    scanf("%f%f%f",&a, &b, &r);
    sr = rectangle(a,b);
    sc =  circle(r);
    s = sr + sc;
    printf(" Summary square is %8.3f\n", s);
    return 0;
}
