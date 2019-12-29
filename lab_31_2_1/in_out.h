#ifndef IN_OUT_H
#define IN_OUT_H
#include "structures.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "constants.h"

int compare_float(const float a, const float b);
int compare_str(const char *a, const char *b);
void free_struct(predmet_t *cur);
void free_arr(predmet_t **arr, int len);
void print_struct(const predmet_t *cur);
void print_arr(predmet_t **arr, int len);
predmet_t* allocate(const char *name, const float mass, const float volume);
int input(FILE *f, char *name, float *mass, float *volume);
int read_file_and_count_strc(FILE *f, int *len);
int read_file_and_add_arr(FILE *f, predmet_t **arr, int len);
void find_substring(predmet_t **arr, int len, char *substring);



#endif // IN_OUT_H

