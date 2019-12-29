#ifndef SORT_H
#define SORT_H
#include <stdbool.h>
#include "constants.h"
#include "structures.h"

bool sort_by_birthday(const pupil *a, const pupil *b);
bool sort_by_grade(const pupil *a, const pupil *b);
bool sort_by_sex(const pupil *a, const pupil *b);
bool sort_by_surname(const pupil *a, const pupil *b);
void arr_sort(pupil_arr *arr, bool(*cmp)(const pupil *a, const pupil *b));

#endif // SORT_H
