#ifndef IN_OUT_H
#define IN_OUT_H

#include "structure.h"

struct number *list_create_node(int n, int pow);
struct number *list_add_begin(struct number *head, struct number *node);
struct number *list_add_end(struct number *head, struct number *node);
void list_print(struct number *head);
void list_free(struct number *head);
void list_inverse(struct number **head);

#endif // IN_OUT_H
