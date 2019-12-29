#ifndef ARR_STRUCT_H
#define ARR_STRUCT_H
#include "structures.h"

void arr_init(pupil_arr *arr);
int arr_append(pupil_arr *arr, pupil *current);
void arr_print(FILE *f, const pupil_arr *arr);
void arr_free(pupil_arr *arr);
int arr_delete(pupil_arr *arr, int index);

#endif // ARR_STRUCT_H
