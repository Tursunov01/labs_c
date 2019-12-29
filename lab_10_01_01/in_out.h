#ifndef IN_OUT_H
#define IN_OUT_H
#include <stdio.h>
#include "structures.h"

int input_and_check_for_overflow(char *str);
int input_arr_grades(int *num_grades, int *grades);
pupil*pupil_create(const char *surname, const char *sex, birthdate cur, int num_grades, int *grades);
void pupil_free(pupil *current);
int pupil_input(pupil **current);
void pupil_print(FILE *f, const pupil *current);

#endif // IN_OUT_H
