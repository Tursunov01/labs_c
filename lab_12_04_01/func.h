#ifndef FUNC_H
#define FUNC_H

#include <stdbool.h>

#include "structure.h"

int create_node_and_add_list(struct number **list, int number, int power);
int reallocate(int **arr, int n);
bool check_prime_num(int n);
int break_up_num(int num, int **arr, int *k);
int count_and_input_pow(int *arr, struct number **list, int k);
int multiplier_divider(int n, struct number **list);
int choose_key(char *key);
struct number *list_find_equal(struct number *head, int what);
struct number *list_find_less(struct number *head, int what);

#endif // FUNC_H
