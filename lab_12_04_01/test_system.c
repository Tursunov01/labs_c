#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "constants.h"
#include "structure.h"
#include "func.h"
#include "operations.h"
#include "in_out.h"

int check_two_arr(int *a, int b[MAX], int len1, int len2)
{
    int rc = OK;
    if (len1 != len2)
        return ERR_RANGE;
    for (int i = 0; i < len1 && rc == OK; i++)
    {
        if (a[i] != b[i])
            rc = ERR_RANGE;
    }
    return rc;
}

int check_len(struct number *list1, struct number *list2)
{
    int n = 0, m = 0;
    struct number *iter1 = list1, *iter2 = list2;
    while (iter1)
    {
        n++;
        iter1 = iter1->next;
    }
    while (iter2)
    {
        m++;
        iter2 = iter2->next;
    }
    if (n != m)
        return ERR_RANGE;
    return OK;
}

int check_two_lists(struct number *list1, struct number *list2)
{
    int rc = OK;
    struct number *iter1 = list1, *iter2 = list2;
    if (check_len(list1, list2) != OK)
        return ERR_RANGE;
    while (iter1 && iter2 && rc == OK)
    {
        if (iter1->num == iter2->num && iter1->power == iter2->power)
        {
            iter1 = iter1->next;
            iter2 = iter2->next;
        }
        else
            rc = ERR_RANGE;
    }
    return rc;
}

void test_check_prime_number(void)
{
    int errors = 0;
    {
        int n = 17;
        if (check_prime_num(n) == false)
            errors++;
    }
    {
        int n = 18;
        if (check_prime_num(n) == true)
            errors++;
    }
    {
        int n = 1;
        if (check_prime_num(n) == true)
            errors++;
    }
    printf("Results of test of function check_prime_number is %d/3\n", errors);
}

void test_break_up_num(void)
{
    int errors = 0;
    {
        int k = 0;
        int *arr = NULL;
        int b[MAX] = { 2, 2, 2, 2 };
        arr = malloc(sizeof(int));
        assert(arr);
        if (break_up_num(16, &arr, &k) == OK)
        {
            if (check_two_arr(arr, b, 4, 4) != OK)
                errors++;
        }
        free(arr);
    }
    {
        int k = 0;
        int *arr = NULL;
        int b[MAX] = { 2, 3, 5, 6 };
        arr = malloc(sizeof(int));
        assert(arr);
        if (break_up_num(150, &arr, &k) == OK)
        {
            if (check_two_arr(arr, b, 4, 4) == OK)
                errors++;
        }
        free(arr);
    }
    printf("Results of test of function break_up_num is %d/2\n", errors);
}

void test_count_and_input_pow(void)
{
    int errors = 0;
    {
        int rc1, rc2, rc3, rc4;
        struct number *list1 = NULL, *list2 = NULL;
        int arr[MAX] = { 2, 2, 3, 3, 5, 11 };

        rc1 = create_node_and_add_list(&list2, 2, 2);
        rc2 = create_node_and_add_list(&list2, 3, 2);
        rc3 = create_node_and_add_list(&list2, 5, 1);
        rc4 = create_node_and_add_list(&list2, 11, 1);

        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK)
        {
            if (count_and_input_pow(arr, &list1, 6) == OK)
            {
                if (check_two_lists(list1, list2) != OK)
                    errors++;
            }
        }
        list_free(list1);
        list_free(list2);
    }
    {
        int rc;
        struct number *list1 = NULL, *list2 = NULL;
        int arr[MAX] = { 5 };

        rc = create_node_and_add_list(&list2, 5, 1);
        
        if (rc == OK)
        {
            if (count_and_input_pow(arr, &list1, 1) == OK)
            {
                if (check_two_lists(list1, list2) != OK)
                    errors++;
            }
        }
        list_free(list1);
        list_free(list2);
    }
    printf("Number of errors of function count_and_input_pow is %d/2\n", errors);
}

void test_list_find_equal(void)
{
    int errors = 0;
    {
        int rc1, rc2, rc3, rc4;
        struct number *list = NULL, *cur = NULL;
        
        rc1 = create_node_and_add_list(&list, 2, 2);
        rc2 = create_node_and_add_list(&list, 3, 2);
        rc3 = create_node_and_add_list(&list, 5, 1);
        rc4 = create_node_and_add_list(&list, 11, 1);

        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK)
        {
            cur = list_find_equal(list, 3);
            if (cur == NULL)
                errors++;
        }
        list_free(list);
    }
    {
        int rc1, rc2, rc3, rc4;
        struct number *list = NULL, *cur = NULL;
        
        rc1 = create_node_and_add_list(&list, 2, 2);
        rc2 = create_node_and_add_list(&list, 3, 2);
        rc3 = create_node_and_add_list(&list, 5, 1);
        rc4 = create_node_and_add_list(&list, 11, 1);

        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK)
        {
            cur = list_find_equal(list, 7);
            if (cur != NULL)
                errors++;
        }
        list_free(list);
    }
    printf("Number of errors in function list_find_equal is %d/2\n", errors);
}

void test_list_find_less(void)
{
    int errors = 0;
    {
        int rc1, rc3, rc4;
        struct number *list = NULL, *cur = NULL;
        
        rc1 = create_node_and_add_list(&list, 2, 2);
        rc3 = create_node_and_add_list(&list, 5, 1);
        rc4 = create_node_and_add_list(&list, 11, 1);

        if (rc1 == OK && rc3 == OK && rc4 == OK)
        {
            cur = list_find_less(list, 3);
            if (cur == NULL)
                errors++;
        }
        list_free(list);
    }
    {
        int rc1, rc2, rc3, rc4;
        struct number *list = NULL, *cur = NULL;
        
        rc1 = create_node_and_add_list(&list, 2, 2);
        rc2 = create_node_and_add_list(&list, 3, 2);
        rc3 = create_node_and_add_list(&list, 5, 1);
        rc4 = create_node_and_add_list(&list, 11, 1);

        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK)
        {
            cur = list_find_less(list, 17);
            if (cur != NULL)
                errors++;
        }
        list_free(list);
    }
    printf("Number of errors in function list_find_less is %d/2\n", errors);
}

void test_list_inverse(void)
{
    int errors = 0;
    {
        int rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8;
        struct number *list1 = NULL, *list2 = NULL;
        
        rc1 = create_node_and_add_list(&list1, 2, 2);
        rc2 = create_node_and_add_list(&list1, 3, 2);
        rc3 = create_node_and_add_list(&list1, 5, 1);
        rc4 = create_node_and_add_list(&list1, 11, 1);

        rc5 = create_node_and_add_list(&list2, 11, 1);
        rc6 = create_node_and_add_list(&list2, 5, 1);
        rc7 = create_node_and_add_list(&list2, 3, 2);
        rc8 = create_node_and_add_list(&list2, 2, 2);

        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK && rc7 == OK && rc8 == OK)
        {
            list_inverse(&list1);
            if (check_two_lists(list1, list2) != OK)
                errors++;
        }
        list_free(list1);
        list_free(list2);
    }
    {
        int rc1, rc2;
        struct number *list1 = NULL, *list2 = NULL;
        
        rc1 = create_node_and_add_list(&list1, 2, 2);
        rc2 = create_node_and_add_list(&list2, 2, 2);

        if (rc1 == OK && rc2 == OK)
        {
            list_inverse(&list1);
            if (check_two_lists(list1, list2) != OK)
                errors++;
        }
        list_free(list1);
        list_free(list2);
    }
    printf("Number of errors in function list_inverse is %d/2\n", errors);
}

void test_operation(void)
{
    int errors = 0;
    {
        int rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8;
        struct number *list1 = NULL, *list2 = NULL, *list3 = NULL;
        
        rc1 = create_node_and_add_list(&list1, 2, 2);
        rc2 = create_node_and_add_list(&list1, 3, 2);
        rc3 = create_node_and_add_list(&list1, 5, 1);
        rc4 = create_node_and_add_list(&list1, 11, 1);

        rc5 = create_node_and_add_list(&list2, 2, 4);
        rc6 = create_node_and_add_list(&list2, 3, 4);
        rc7 = create_node_and_add_list(&list2, 5, 2);
        rc8 = create_node_and_add_list(&list2, 11, 2);

        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK && rc7 == OK && rc8 == OK)
        {
            rc1 = operation(list1, list1, &list3, '*');
            if (check_two_lists(list3, list2) != OK)
                errors++;
        }
        list_free(list1);
        list_free(list2);
        list_free(list3);
    }
    {
        int rc1, rc2, rc3, rc4, rc5, rc7;
        struct number *list1 = NULL, *list2 = NULL, *list3 = NULL, *list4 = NULL;
        
        rc1 = create_node_and_add_list(&list1, 2, 2);
        rc2 = create_node_and_add_list(&list1, 3, 2);
        rc3 = create_node_and_add_list(&list1, 5, 1);
        rc4 = create_node_and_add_list(&list1, 11, 1);

        rc1 = create_node_and_add_list(&list4, 2, 1);
        rc2 = create_node_and_add_list(&list4, 3, 2);
        rc4 = create_node_and_add_list(&list4, 11, 1);

        rc5 = create_node_and_add_list(&list2, 2, 1);
        rc7 = create_node_and_add_list(&list2, 5, 1);

        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc7 == OK)
        {
            rc1 = operation(list1, list2, &list3, '/');
            if (check_two_lists(list3, list4) != OK)
                errors++;
        }
        list_free(list1);
        list_free(list2);
        list_free(list3);
        list_free(list4);
    }
    printf("Number of errors in function operation is %d/2\n", errors);
}

int main(void)
{
    setbuf(stdout, NULL);
    test_check_prime_number();
    test_break_up_num();
    test_count_and_input_pow();
    test_list_find_equal();
    test_list_find_less();
    test_list_inverse();
    test_operation();

    return 0;
}