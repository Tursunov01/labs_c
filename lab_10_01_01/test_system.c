#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "delete.h"
#include "func.h"
#include "insert.h"
#include "sort.h"
#include "constants.h"
#include "structures.h"
#include "in_out.h"
#include "arr_struct.h"

int compare_num(double n1, double n2)
{
    if (fabs(n1 - n2) < EPS)
        return 1;
    return 0;
}

int compare_arr_struct(const pupil_arr *a, const pupil_arr *b)
{
    if (a->len - b->len != 0)
        return 0;
    for (int i = 0; i < a->len; i++)
    {
        if (strcmp(a->data[i]->surname, b->data[i]->surname) != 0)
            return 0;
        if (strcmp(a->data[i]->sex, b->data[i]->sex) != 0)
            return 0;
        if (a->data[i]->date.year != b->data[i]->date.year)
            return 0;
        if (a->data[i]->date.month != b->data[i]->date.month)
            return 0;
        if (a->data[i]->date.day != b->data[i]->date.day)
            return 0;
        if (a->data[i]->num_grades - b->data[i]->num_grades != 0)
            return 0;
        for (int j = 0; j < a->data[i]->num_grades; j++)
        {
            if (a->data[i]->grades[j] - b->data[i]->grades[j] != 0)
                return 0;
        }
    }
    return 1;
}

void test_check_leap_year(void)
{
    int errors = 0;
    {
        if (check_leap_year(2016) != OK)
            errors++;
    }
    {
        if (check_leap_year(2124) != OK)
            errors++;
    }
    {
        if (check_leap_year(2100) == OK)
            errors++;
    }
    {
        if (check_leap_year(1700) == OK)
            errors++;
    }
    {
        if (check_leap_year(0) != OK)
            errors++;
    }
    printf("Number of errors in function check_leap_year is %d/5\n", errors);
}

void test_check_surname(void)
{
    int errors = 0;
    {
        char str[] = "камилла";
        if (check_surname(str) == OK)
            errors++;
    }
    {
        char str[] = "dasdasкамилла";
        if (check_surname(str) == OK)
            errors++;
    }
    {
        char str[] = "12Kirill";
        if (check_surname(str) == OK)
            errors++;
    }
    {
        char str[] = "K1r2rl";
        if (check_surname(str) == OK)
            errors++;
    }
    printf("Number of errors in function check_surname is %d/4\n", errors);
}


void test_cmp_case_insentive(void)
{
    int errors = 0;
    {
        char a[] = "Jackson", b[] = "jAckSOn";
        if (cmp_case_insentive(a, b) != 0)
            errors++;
    }
    {
        char a[] = "ivchenko", b[] = "IVCHENKO";
        if (cmp_case_insentive(a, b) != 0)
            errors++;
    }
    {
        char a[] = "misha", b[] = "masha";
        if (cmp_case_insentive(a, b) == 0)
            errors++;
    }
    printf("Number of errors in function cmp_case_insentive is %d/3\n", errors);
}

void test_check_birthday(void)
{
    int errors = 0;
    {
        char birthday[] = "2000.12.32";
        birthdate cur;
        if (check_birthday(birthday, &cur) == OK)
            errors++;
    }
    {
        char birthday[] = "2000.14.25";
        birthdate cur;
        if (check_birthday(birthday, &cur) == OK)
            errors++;
    }
    {
        char birthday[] = "2000.11.2";
        birthdate cur;
        if (check_birthday(birthday, &cur) == OK)
            errors++;
    }
    {
        char birthday[] = "2000.9.20";
        birthdate cur;
        if (check_birthday(birthday, &cur) == OK)
            errors++;
    }
    {
        char birthday[] = "0000.9.20";
        birthdate cur;
        if (check_birthday(birthday, &cur) == OK)
            errors++;
    }
    printf("Number of errors in function check_birthday is %d/3\n", errors);
}

/*Вторая ошибка была связана тесно с первой. Начальный формат объявления структуры выглядело именно так,
 * но когда я передавал в "pupil create" структуру в виде "cur", компилятор ругался. Замечание его было
 * исправлено на "&cur". После измений компилятор проверил всё и не нашёл ошибок. После запуска самой программы
 * "test.exe", компилятор показывал результаты тестов и возвращал код ошибки 0. После чего программа не билдилась
 * на сервере. Потом пришлось пропускать весь проект через компилятор на ubuntu, которая сразу нашла первую ошибку
 * (см файл in_out.c), а valgrind выдавал segmentation fault при вызове этой и последующих функций. После
 * проставления отладочной печати, мне удалось найти уязвимые места(см ниже).*/
void test_check_age(void)
{
    int errors = 0;
    {
        pupil *current = NULL;
        int marks[] = { 1, 5 };
        birthdate cur;
        cur.year = 2000;
        cur.month = 21;
        cur.day = 5;
        //вызов функции pupil_create был неверным
        current = pupil_create("Agzamov", "male", cur, 2, marks);
        if (check_age(current, 17) == LESS_AGE)
            errors++;
        pupil_free(current);
    }
    {
        pupil *current = NULL;
        int marks[] = { 2, 5, 3 };
        birthdate cur;
        cur.year = 2002;
        cur.month = 12;
        cur.day = 15;
        current = pupil_create("Zohidov", "male", cur, 3, marks);
        if (check_age(current, 17) != LESS_AGE)
            errors++;
        pupil_free(current);
    }
    {
        pupil *current = NULL;
        int marks[] = { 2, 5, 3 };
        birthdate cur;
        cur.year = 2002;
        cur.month = 11;
        cur.day = 1;
        current = pupil_create("Zaripova", "female", cur, 3, marks);
        if (check_age(current, 17) == LESS_AGE)
            errors++;
        pupil_free(current);
    }
    printf("Number of errors in function check_age is %d/3\n", errors);
}

void test_average(void)
{
    int errors = 0;
    {
        int marks[] = { 4 };
        if (compare_num(average(1, marks), 4) == 0)
            errors++;
    }
    {
        int marks[] = { 5, 2, 4, 0, 1 };
        if (compare_num(average(5, marks), 2.4) == 0)
            errors++;
    }
    {
        int marks[] = { 5, 2, 4 };
        if (compare_num(average(3, marks), 3.666667) == 0)
            errors++;
    }
    printf("Number of errors in function average is %d/3\n", errors);
}

void test_delete_girls(void)
{
    int errors = 0;
    {
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        birthdate cur1;
        cur1.year = 2000;
        cur1.month = 5;
        cur1.day = 5;
        birthdate cur2;
        cur2.year = 2002;
        cur2.month = 11;
        cur2.day = 5;
        birthdate cur3;
        cur3.year = 1999;
        cur3.month = 5;
        cur3.day = 8;
        int marks[] = { 1, 4 };
        candidate1 = pupil_create("Agzamova", "female", cur1, 2, marks);
        candidate2 = pupil_create("Yusupova", "female", cur2, 2, marks);
        candidate3 = pupil_create("Kim", "male", cur3, 2, marks);
        candidate4 = pupil_create("Yusupova", "female", cur2, 2, marks);
        candidate5 = pupil_create("Kim", "male", cur3, 2, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc5 = arr_append(&b, candidate5);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK)
        {
            rc1 = delete_girls(&a, "female", 17);
            if (rc1 == OK)
            {
                if (compare_arr_struct(&a, &b) == 0)
                    errors++;
            }
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate6 = NULL;
        int marks[] = { 1, 4 };
        birthdate cur1;
        cur1.year = 2004;
        cur1.month = 5;
        cur1.day = 5;
        birthdate cur2;
        cur2.year = 2002;
        cur2.month = 11;
        cur2.day = 1;
        birthdate cur3;
        cur3.year = 1999;
        cur3.month = 5;
        cur3.day = 8;
        candidate1 = pupil_create("Agzamova", "female", cur1, 2, marks);
        candidate2 = pupil_create("Yusupova", "female", cur2, 2, marks);
        candidate3 = pupil_create("Kim", "male", cur3, 2, marks);
        candidate4 = pupil_create("Agzamova", "female", cur1, 2, marks);
        candidate6 = pupil_create("Kim", "male", cur3, 2, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc6 = arr_append(&b, candidate6);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc6 == OK)
        {
            rc1 = delete_girls(&a, "female", 17);
            if (rc1 == OK)
            {
                if (compare_arr_struct(&a, &b) == 0)
                    errors++;
            }
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        birthdate cur2;
        cur2.year = 2002;
        cur2.month = 11;
        cur2.day = 1;
        birthdate cur3;
        cur3.year = 1999;
        cur3.month = 5;
        cur3.day = 8;
        int marks[] = { 1, 4 };
        candidate1 = pupil_create("Agzamova", "female", cur1, 2, marks);
        candidate2 = pupil_create("Yusupova", "female", cur2, 2, marks);
        candidate3 = pupil_create("Kim", "female", cur3, 2, marks);
        candidate4 = pupil_create("Agzamova", "female", cur1, 2, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK)
        {
            rc1 = delete_girls(&a, "female", 17);
            if (rc1 == OK)
            {
                if (compare_arr_struct(&a, &b) == 0)
                    errors++;
            }
        }
        arr_free(&a);
        arr_free(&b);
    }
    printf("Number of errors in function delete_girls is %d/3\n", errors);
}

void test_insert_grade(void)
{
    int errors = 0;
    {
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        int marks1[] = { 4 };
        int marks2[] = { 4, 3 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        candidate1 = pupil_create("Agzamova", "female", cur1, 1, marks1);
        candidate2 = pupil_create("Agzamova", "female", cur1, 2, marks2);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&b, candidate2);
        if (rc1 == OK && rc2 == OK)
        {
            rc1 = insert_grade(&a);
            if (rc1 == OK)
            {
                if (compare_arr_struct(&a, &b) == 0)
                    errors++;
            }
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        int marks1[] = { 5, 2, 3 };
        int marks2[] = { 5, 2, 3, 3 };
        candidate1 = pupil_create("Agzamova", "female", cur1, 3, marks1);
        candidate2 = pupil_create("Agzamova", "female", cur1, 4, marks2);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&b, candidate2);
        if (rc1 == OK && rc2 == OK)
        {
            rc1 = insert_grade(&a);
            if (rc1 == OK)
            {
                if (compare_arr_struct(&a, &b) == 0)
                    errors++;
            }
        }
        arr_free(&a);
        arr_free(&b);
    }
    printf("Number of errors in function insert_grade is %d/2\n", errors);
}

void test_arr_delete(void)
{
    int errors = 0;
    {
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        birthdate cur2;
        cur2.year = 2002;
        cur2.month = 11;
        cur2.day = 5;
        birthdate cur3;
        cur3.year = 1999;
        cur3.month = 5;
        cur3.day = 8;
        candidate1 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate2 = pupil_create("Yusupova", "female", cur2, 1, marks);
        candidate3 = pupil_create("Kim", "female", cur3, 1, marks);
        candidate4 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate5 = pupil_create("Yusupova", "female", cur2, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc5 = arr_append(&b, candidate5);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK)
        {
            rc1 = arr_delete(&a, 2);
            if (rc1 == OK)
            {
                if (compare_arr_struct(&a, &b) == 0)
                    errors++;
            }
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        birthdate cur2;
        cur2.year = 2002;
        cur2.month = 11;
        cur2.day = 5;
        birthdate cur3;
        cur3.year = 1999;
        cur3.month = 5;
        cur3.day = 8;
        candidate1 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate2 = pupil_create("Yusupova", "female", cur2, 1, marks);
        candidate3 = pupil_create("Kim", "female", cur3, 1, marks);
        candidate4 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate5 = pupil_create("Kim", "female", cur3, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc5 = arr_append(&b, candidate5);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK)
        {
            rc1 = arr_delete(&a, 1);
            if (rc1 == OK)
            {
                if (compare_arr_struct(&a, &b) == 0)
                    errors++;
            }
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        birthdate cur2;
        cur2.year = 2002;
        cur2.month = 11;
        cur2.day = 5;
        birthdate cur3;
        cur3.year = 1999;
        cur3.month = 5;
        cur3.day = 8;
        candidate1 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate2 = pupil_create("Yusupova", "female", cur2, 1, marks);
        candidate3 = pupil_create("Kim", "female", cur3, 1, marks);
        candidate4 = pupil_create("Yusupova", "female", cur2, 1, marks);
        candidate5 = pupil_create("Kim", "female", cur3, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc5 = arr_append(&b, candidate5);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK)
        {
            rc1 = arr_delete(&a, 0);
            if (rc1 == OK)
            {
                if (compare_arr_struct(&a, &b) == 0)
                    errors++;
            }
        }
        arr_free(&a);
        arr_free(&b);
    }
    printf("Number of errors in function arr_delete is %d/3\n", errors);
}

void test_sort(void)
{
    int errors = 0;
    {
        //сортировка по полу(пол у всех одинаковый)
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        pupil *candidate6 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        candidate1 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate2 = pupil_create("Yusupova", "female", cur1, 1, marks);
        candidate3 = pupil_create("Kim", "FEMALE", cur1, 1, marks);
        candidate4 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate5 = pupil_create("Yusupova", "female", cur1, 1, marks);
        candidate6 = pupil_create("Kim", "FEMALE", cur1, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc5 = arr_append(&b, candidate5);
        int rc6 = arr_append(&b, candidate6);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK)
        {
            arr_sort(&a, sort_by_sex);
            if (compare_arr_struct(&a, &b) == 0)
                errors++;
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        //сортировка по полу(пол у всех разный)
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        pupil *candidate6 = NULL;
        pupil *candidate7 = NULL;
        pupil *candidate8 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        candidate1 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate2 = pupil_create("Yusupova", "female", cur1, 1, marks);
        candidate3 = pupil_create("Kim", "FEMALE", cur1, 1, marks);
        candidate4 = pupil_create("Zohidov", "MALE", cur1, 1, marks);
        candidate5 = pupil_create("Yusupova", "female", cur1, 1, marks);
        candidate6 = pupil_create("Kim", "FEMALE", cur1, 1, marks);
        candidate7 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate8 = pupil_create("Zohidov", "MALE", cur1, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&a, candidate4);
        int rc5 = arr_append(&b, candidate5);
        int rc6 = arr_append(&b, candidate6);
        int rc7 = arr_append(&b, candidate7);
        int rc8 = arr_append(&b, candidate8);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK && rc7 == OK && rc8 == OK)
        {
            arr_sort(&a, sort_by_sex);
            if (compare_arr_struct(&a, &b) == 0)
                errors++;
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        //сортировка по фамилии(фамилии у всех одинаковые)
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        pupil *candidate6 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        candidate1 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate2 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate3 = pupil_create("Agzamov", "MALE", cur1, 1, marks);
        candidate4 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate5 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate6 = pupil_create("Agzamov", "MALE", cur1, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc5 = arr_append(&b, candidate5);
        int rc6 = arr_append(&b, candidate6);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK)
        {
            arr_sort(&a, sort_by_surname);
            if (compare_arr_struct(&a, &b) == 0)
                errors++;
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        //сортировка по фамилии(фамилии у всех разные но есть и одинаковые)
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        pupil *candidate6 = NULL;
        pupil *candidate7 = NULL;
        pupil *candidate8 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        candidate1 = pupil_create("agzamov", "male", cur1, 1, marks);
        candidate2 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate3 = pupil_create("AgZaMov", "MALE", cur1, 1, marks);
        candidate4 = pupil_create("Zohidov", "male", cur1, 1, marks);
        candidate5 = pupil_create("AgZaMov", "MALE", cur1, 1, marks);
        candidate6 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate7 = pupil_create("Zohidov", "male", cur1, 1, marks);
        candidate8 = pupil_create("agzamov", "male", cur1, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&a, candidate4);
        int rc5 = arr_append(&b, candidate5);
        int rc6 = arr_append(&b, candidate6);
        int rc7 = arr_append(&b, candidate7);
        int rc8 = arr_append(&b, candidate8);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK && rc7 == OK && rc8 == OK)
        {
            arr_sort(&a, sort_by_surname);
            if (compare_arr_struct(&a, &b) == 0)
                errors++;
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        //сортировка по дате рождения(день рождения у всех одинаковая)
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        pupil *candidate6 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        candidate1 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate2 = pupil_create("Yusupova", "female", cur1, 1, marks);
        candidate3 = pupil_create("Kim", "FEMALE", cur1, 1, marks);
        candidate4 = pupil_create("Agzamova", "female", cur1, 1, marks);
        candidate5 = pupil_create("Yusupova", "female", cur1, 1, marks);
        candidate6 = pupil_create("Kim", "FEMALE", cur1, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc5 = arr_append(&b, candidate5);
        int rc6 = arr_append(&b, candidate6);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK)
        {
            arr_sort(&a, sort_by_birthday);
            if (compare_arr_struct(&a, &b) == 0)
                errors++;
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        //сортировка по дате рождения(дни рождения у всех разные но есть и одинаковые)
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        pupil *candidate6 = NULL;
        pupil *candidate7 = NULL;
        pupil *candidate8 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        birthdate cur2;
        cur2.year = 2002;
        cur2.month = 11;
        cur2.day = 5;
        birthdate cur3;
        cur3.year = 1999;
        cur3.month = 5;
        cur3.day = 8;
        candidate1 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate2 = pupil_create("Agzamov", "male", cur2, 1, marks);
        candidate3 = pupil_create("Abdurashidov", "MALE", cur3, 1, marks);
        candidate4 = pupil_create("Zohidov", "male", cur3, 1, marks);
        candidate5 = pupil_create("Abdurashidov", "MALE", cur3, 1, marks);
        candidate6 = pupil_create("Zohidov", "male", cur3, 1, marks);
        candidate7 = pupil_create("Agzamov", "male", cur2, 1, marks);
        candidate8 = pupil_create("Agzamov", "male", cur1, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&a, candidate4);
        int rc5 = arr_append(&b, candidate5);
        int rc6 = arr_append(&b, candidate6);
        int rc7 = arr_append(&b, candidate7);
        int rc8 = arr_append(&b, candidate8);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK && rc7 == OK && rc8 == OK)
        {
            arr_sort(&a, sort_by_birthday);
            if (compare_arr_struct(&a, &b) == 0)
                errors++;
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        //сортировка по среднему арифметическому(оценки у всех одинаковые)
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        pupil *candidate6 = NULL;
        int marks[] = { 4 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        candidate1 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate2 = pupil_create("Zohidov", "male", cur1, 1, marks);
        candidate3 = pupil_create("Alimov", "MALE", cur1, 1, marks);
        candidate4 = pupil_create("Agzamov", "male", cur1, 1, marks);
        candidate5 = pupil_create("Zohidov", "male", cur1, 1, marks);
        candidate6 = pupil_create("Alimov", "MALE", cur1, 1, marks);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&b, candidate4);
        int rc5 = arr_append(&b, candidate5);
        int rc6 = arr_append(&b, candidate6);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK)
        {
            arr_sort(&a, sort_by_grade);
            if (compare_arr_struct(&a, &b) == 0)
                errors++;
        }
        arr_free(&a);
        arr_free(&b);
    }
    {
        //сортировка по среднему арифметическому(оценки у всех разные но есть и одинаковые)
        pupil_arr a;
        pupil_arr b;
        arr_init(&a);
        arr_init(&b);
        pupil *candidate1 = NULL;
        pupil *candidate2 = NULL;
        pupil *candidate3 = NULL;
        pupil *candidate4 = NULL;
        pupil *candidate5 = NULL;
        pupil *candidate6 = NULL;
        pupil *candidate7 = NULL;
        pupil *candidate8 = NULL;
        int marks1[] = { 3 };
        int marks2[] = { 4, 2, 5, 5 };
        int marks3[] = { 5, 5 };
        birthdate cur1;
        cur1.year = 2013;
        cur1.month = 5;
        cur1.day = 5;
        candidate1 = pupil_create("Agzamov", "male", cur1, 2, marks3);
        candidate2 = pupil_create("Agzamov", "male", cur1, 1, marks1);
        candidate3 = pupil_create("Abdurashidov", "MALE", cur1, 4, marks2);
        candidate4 = pupil_create("Zohidov", "male", cur1, 2, marks3);
        candidate5 = pupil_create("Agzamov", "male", cur1, 1, marks1);
        candidate6 = pupil_create("Abdurashidov", "MALE", cur1, 4, marks2);
        candidate7 = pupil_create("Agzamov", "male", cur1, 2, marks3);
        candidate8 = pupil_create("Zohidov", "male", cur1, 2, marks3);
        int rc1 = arr_append(&a, candidate1);
        int rc2 = arr_append(&a, candidate2);
        int rc3 = arr_append(&a, candidate3);
        int rc4 = arr_append(&a, candidate4);
        int rc5 = arr_append(&b, candidate5);
        int rc6 = arr_append(&b, candidate6);
        int rc7 = arr_append(&b, candidate7);
        int rc8 = arr_append(&b, candidate8);
        if (rc1 == OK && rc2 == OK && rc3 == OK && rc4 == OK && rc5 == OK && rc6 == OK && rc7 == OK && rc8 == OK)
        {
            arr_sort(&a, sort_by_grade);
            if (compare_arr_struct(&a, &b) == 0)
                errors++;
        }
        arr_free(&a);
        arr_free(&b);
    }
    printf("Number of errors in function sort is %d/8\n", errors);
}

int main(void)
{
    setbuf(stdout, NULL);
    test_cmp_case_insentive();
    test_check_birthday();
    test_check_age();
    test_average();
    test_delete_girls();
    test_insert_grade();
    test_arr_delete();
    test_sort();
    test_check_leap_year();
    test_check_surname();
    return 0;
}
