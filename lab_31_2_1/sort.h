#ifndef SORT_H
#define SORT_H
#include "structures.h"

int cmp_density(const predmet_t *curl, const predmet_t *curr);
void arr_sort(predmet_t **arr, int len, int (*cmp)(const predmet_t *curl, const predmet_t *curr));

#endif // SORT_H
