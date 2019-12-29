#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "constants.h"
#include "func.h"

/**
 * \fn cmp_two_str(const char *a, const char *b)
 * \brief Функция, сравнивающая 2 строки.
 * \param [in] a - сравниваемая строка.
 * \param [in] b - сравниваемая строка.
 * \return результат сравнения.
 */

int cmp_two_str(const char *a, const char *b)
{
    int i = 0;
    if (my_strlen(a) != my_strlen(b))
        return NOT_EQUAL;
    while (a[i] != '\0')
    {
        if (a[i] != b[i])
            return NOT_EQUAL;
        i++;
    }
    return OK;
}

void test_spec()
{
    int error_len = 0, error_buf = 0;
    {
        char my[MAX] = { 0 };
        char original[MAX];
        int n = my_snprintf(my, 0, "%s", "123456");
        int k = snprintf(original, 0, "%s", "123456");
        printf("my_snprintf = %d\nsn_printf = %d\n", n, k);
        printf("my_snprintf = %s\nsn_printf = %s\n", my, original);
        if (strcmp(my, original) != 0)
            printf("Error! Not equal\n");
        else
            printf("OK!\n");
    }
}

void test_spec_s(char *spec, char *str)
{
    int error_len = 0, error_buf = 0;
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, spec, str);
        int k = snprintf(original, 3, spec, str);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, spec, str);
        int k = snprintf(original, 99, spec, str);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    printf("------------------------------------------------------------------\n");
    //printf("\t  Results of testing the specificator '%s' is in value '%s':\n", spec, str);
    printf("Number of errors in len is %d.\nNumber of errors in buf is %d.\n", error_len, error_buf);
}

void test_spec_d()
{
    int error_len = 0, error_buf = 0;
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, "%d", INT_MAX);
        int k = snprintf(original, 3, "%d", INT_MAX);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, "%d", INT_MAX);
        int k = snprintf(original, 99, "%d", INT_MAX);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, "%d", INT_MIN);
        int k = snprintf(original, 3, "%d", INT_MIN);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, "%d", INT_MIN);
        int k = snprintf(original, 99, "%d", INT_MIN);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, "%d", -01);
        int k = snprintf(original, 3, "%d", -01);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, "%d", -01);
        int k = snprintf(original, 99, "%d", -01);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, "%d", 00);
        int k = snprintf(original, 3, "%d", 00);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, "%d", 00);
        int k = snprintf(original, 99, "%d", 00);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    printf("------------------------------------------------------------------\n");
    printf("Number of errors in len is %d.\nNumber of errors in buf is %d.\n", error_len, error_buf);
}

void test_spec_ho()
{
    int error_len = 0, error_buf = 0;
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, "%ho", USHRT_MAX);
        int k = snprintf(original, 3, "%ho", USHRT_MAX);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, "%ho", USHRT_MAX);
        int k = snprintf(original, 99, "%ho", USHRT_MAX);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, "%ho", 0x0);
        int k = snprintf(original, 3, "%ho", 0x0);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, "%ho", 0x0);
        int k = snprintf(original, 99, "%ho", 0x0);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, "%ho", 0144);
        int k = snprintf(original, 3, "%ho", 0144);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, "%ho", 0144);
        int k = snprintf(original, 99, "%ho", 0144);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 3, "%ho", 00);
        int k = snprintf(original, 3, "%ho", 00);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    {
        char my[MAX] = "";
        char original[MAX] = "";
        int n = my_snprintf(my, 99, "%ho", 00);
        int k = snprintf(original, 99, "%ho", 00);
        if (n != k)
            error_len++;
        if (cmp_two_str(my, original) != OK)
            error_buf;
    }
    printf("------------------------------------------------------------------\n");
    printf("Number of errors in len is %d.\nNumber of errors in buf is %d.\n", error_len, error_buf);
}

int main(void)
{
    setbuf(stdout, NULL);
    printf("\t  TESTING RESULTS\n");
    //test_spec();
    test_spec_s("%s", "");
    test_spec_s("%s", "jasur_09");
    test_spec_s("%s", ",real_madrid!");
    test_spec_s("%s", "rr,ttt.t.t!ss,@@@");
    test_spec_d();
    test_spec_ho();
    return OK;
}
