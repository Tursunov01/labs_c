#ifndef IN_OUT_H
#define IN_OUT_H

#include "structures.h"

void free_struct(person_t *cur);

void free_arr(person_t **arr, int len);

void print_struct(person_t *cur);

void print_arr(person_t **arr, int len);

person_t* allocate(const char *surname, int year);

int read_file(FILE *f, char *surname, int *year);

int count_len(FILE *f, int *len);

int add_arr(FILE *f, person_t **arr, int len);

int check_arr(person_t **arr, int len, person_t *cur);

int delete_equal(person_t **arr, int index, int *len);

int check_struct(person_t **arr, int index, int len, person_t *cur, int *pos);

int union_arr(person_t **res, person_t **a, person_t **b, int len1, int len2);

#endif // IN_OUT_H