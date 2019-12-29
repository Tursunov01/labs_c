#ifndef IN_OUT_H
#define IN_OUT_H

void matrix_free(int64_t **a, int n);
int64_t**matrix_alloc(int n, int m);
int matrix_input(int64_t **a, int n, int m);
int matrix_create(int64_t ***a, int *n, int *m);
void matrix_print(int64_t **a, int n, int m);
int input_powers(int *r, int *y);

#endif // IN_OUT_H
