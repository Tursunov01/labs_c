#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_out.h"
#include "sort.h"
#include "structures.h"
#include "constants.h"

int compare_num(double n1, double n2)
{
    if (fabs(n1 - n2) < EPS)
        return 1;
    return 0;
}

int compare_arr_struct(predmet_t **a, predmet_t **b, int len1, int len2)
{
    if (len1 - len2 != 0)
        return 0;
    for (int i = 0; i < len1; i++)
    {
        if (strcmp(a[i]->name, b[i]->name) != 0)
            return 0;
        if (a[i]->mass != b[i]->mass)
            return 0;
        if (a[i]->volume != b[i]->volume)
            return 0;
    }
    return 1;
}

void test_cmp_density(void)
{
    int errors = 0;
    {
        predmet_t l = { .name = "zoloto", .mass = 10, .volume = 20 }; 
        predmet_t r = { .name = "serebro", .mass = 50, .volume = 10 };
        if (cmp_density(&l, &r) == 1)
            errors++;
    }
    {
        predmet_t l = { .name = "zoloto", .mass = 100, .volume = 3 }; 
        predmet_t r = { .name = "serebro", .mass = 12, .volume = 10 };
        if (cmp_density(&l, &r) == 0)
            errors++;
    }
    printf("Number of errors of function cmp_density is %d/2\n", errors);
}

void test_sort(void)
{
    int errors = 0;
    {
        predmet_t **arr = NULL, **res = NULL;
        predmet_t *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *l1 = NULL, *l2 = NULL, *l3 = NULL, *l4 = NULL;
        arr = malloc(4 * sizeof(predmet_t*));
        res = malloc(4 * sizeof(predmet_t*));

        char name1[MAX] = "zoloto";
        float mass1 = 10, volume1 = 20;

        char name2[MAX] = "serebro";
        float mass2 = 50, volume2  = 10;
        
        char name3[MAX] = "med";
        float mass3 = 1, volume3 = 3;
        
        char name4[MAX] = "platinum";
        float mass4 = 3, volume4 = 4;

        r1 = allocate(name1, mass1, volume1);
        r2 = allocate(name2, mass2, volume2);
        r3 = allocate(name3, mass3, volume3);
        r4 = allocate(name4, mass4, volume4);

        l1 = allocate(name1, mass1, volume1);
        l2 = allocate(name2, mass2, volume2);
        l3 = allocate(name3, mass3, volume3);
        l4 = allocate(name4, mass4, volume4);
        
        arr[0] = r1;
        arr[1] = r2;
        arr[2] = r3;
        arr[3] = r4;

        res[0] = l3;
        res[1] = l1;
        res[2] = l4;
        res[3] = l2;

        arr_sort(arr, 4, cmp_density);
        if (compare_arr_struct(arr, res, 4, 4) == 0)
            errors++;
        free_arr(arr, 4);
        free_arr(res, 4);
    }
    {
        predmet_t **arr = NULL, **res = NULL;
        predmet_t *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *l1 = NULL, *l2 = NULL, *l3 = NULL, *l4 = NULL;
        arr = malloc(4 * sizeof(predmet_t*));
        res = malloc(4 * sizeof(predmet_t*));

        char name1[MAX] = "zoloto";
        float mass1 = 10, volume1 = 20;

        char name2[MAX] = "serebro";
        float mass2 = 50, volume2  = 10;
        
        char name3[MAX] = "med";
        float mass3 = 1, volume3 = 3;
        
        char name4[MAX] = "platinum";
        float mass4 = 3, volume4 = 4;

        r1 = allocate(name1, mass1, volume1);
        r2 = allocate(name2, mass2, volume2);
        r3 = allocate(name3, mass3, volume3);
        r4 = allocate(name4, mass4, volume4);

        l1 = allocate(name1, mass1, volume1);
        l2 = allocate(name2, mass2, volume2);
        l3 = allocate(name3, mass3, volume3);
        l4 = allocate(name4, mass4, volume4);
        
        arr[0] = r2;
        arr[1] = r1;
        arr[2] = r4;
        arr[3] = r3;

        res[0] = l3;
        res[1] = l1;
        res[2] = l4;
        res[3] = l2;

        arr_sort(arr, 4, cmp_density);
        if (compare_arr_struct(arr, res, 4, 4) == 0)
            errors++;
        free_arr(arr, 4);
        free_arr(res, 4);
    }
    
    printf("Number of errors of function sort is %d/2\n", errors);
}

void test_compare_float(void)
{
    int errors = 0;
    {
        float a = 15.3, b = 10.8;
        if (compare_float(a, b) == 1)
            errors++;
    }
    {
        float a = 5, b = 5;
        if (compare_float(a, b) == 0)
            errors++;
    }
    printf("Number of errors in function compare_float is %d/2\n", errors);
}

void test_compare_str(void)
{
    int errors = 0;
    {
        char a[MAX] = "aurum", b[MAX] = "au";
        if (compare_str(a, b) == 0)
            errors++;
    }
    {
        char a[MAX] = "aurum", b[MAX] = "aul";
        if (compare_str(a, b) == 1)
            errors++;
    }
    printf("Number of errors in function compare_str is %d/2\n", errors);
}

void test_read_file_and_count_len(void)
{
    int errors = 0;
    {
        int len = 0;
        FILE *f;
        f = fopen("data.txt", "r");
        if (read_file_and_count_strc(f, &len) == OK)
        {
            if (len != 2)
                errors++;
        }
        fclose(f);
    }
    {
        int len = 0;
        FILE *f;
        f = fopen("data1.txt", "r");
        if (read_file_and_count_strc(f, &len) == OK)
        {
            if (len != 0)
                errors++;
        }
        fclose(f);
    }
    printf("Number of errors of function which count structures is %d/2\n", errors);
}

int main(void)
{
    setbuf(stdout, NULL);
    test_cmp_density();
    test_sort();
    test_compare_float();
    test_compare_str();
    test_read_file_and_count_len();
    return 0;
}