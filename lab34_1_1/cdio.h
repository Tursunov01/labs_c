#ifndef CDIO_H
#define CDIO_H

#include "structures.h"

struct node_t* list_create(int num);

struct node_t* list_add_begin(struct node_t *head, struct node_t *node);

struct node_t* list_add_end(struct node_t *head, struct node_t *node);

void list_print(struct node_t *head);

void list_free(struct node_t *head);

struct node_t* read_file(FILE *f);

struct node_t* delete(struct node_t *head, int what);

float srednee(struct node_t *head, int *n);

struct node_t* oper_del(struct node_t *head, float sum);


#endif // CDIO_H
