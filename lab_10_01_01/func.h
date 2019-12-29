#ifndef FUNC_H
#define FUNC_H
#include "structures.h"

int cmp_case_insentive(const char *a, const char *b);
int check_birthday(const char *birthday, birthdate *date);
int valid_date(birthdate *cur);
int check_age(const pupil *kids, int age);
double average(int n, int *grades);
int sort_with_key(pupil_arr *arr);
int check_surname(const char *surname);
int check_leap_year(int year);

#endif // FUNC_H
