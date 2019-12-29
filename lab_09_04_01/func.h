#ifndef FUNC_H
#define FUNC_H

void find_pos_max(int64_t **a, int n, int m, int *p_c, int *p_r);
void move_up(int64_t **a, int n, int k);
void move_left(int64_t **a, int n, int m, int k);
int resize_column(int64_t **a, int n, int m);
int resize_row(int64_t ***a, int n);
int add_row(int64_t ***a, int n, int m);
int64_t average(int64_t **a, int n, int k);
int64_t find_min(int64_t **a, int m, int k);
int copy_and_add(int64_t ***a, int *n, int m, const int64_t *arr, int n_row);

#endif // FUNC_H
