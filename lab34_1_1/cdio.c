#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "structures.h"
#include "cdio.h"

struct node_t* list_create(int num)
{
    struct node_t *node = malloc(sizeof(struct node_t));
    if (node)
    {
        node->num = num;
        node->next = NULL;
    }
    return node;
}

struct node_t* list_add_begin(struct node_t *head, struct node_t *node)
{
    node->next = head;
    return node;
}

struct node_t* list_add_end(struct node_t *head, struct node_t *node)
{
    if (!head)
        return node;
    struct node_t *iter = head;
    while(iter->next)
        iter = iter->next;
    iter->next = node;
    return head;
}

void list_print(struct node_t *head)
{
    struct node_t *iter = head;
    while (iter)
    {
        printf("%d ", iter->num);
        iter = iter->next;
    }
    printf("\n");
}

void list_free(struct node_t *head)
{
    struct node_t *iter = head, *del;
    while(iter)
    {
        del = iter;
        iter = iter->next;
        free(del);
    }
}

struct node_t* read_file(FILE *f)
{
    struct node_t *head = NULL, *node;
    int num;
    while (fscanf(f, "%d", &num) == 1)
    {
        node = list_create(num);
        head = list_add_end(head, node);
    }
    return head;
}

struct node_t* delete(struct node_t *head, int what)
{
    struct node_t *iter = head, *prev = NULL, *del;
    while (iter)
    {
        if (iter->num == what)
        {
            del = iter;
            if (prev)
                prev->next = iter = iter->next;
            else
                head = iter = iter->next;
            free(del);
        }
        else
        {
            prev = iter;
            iter = iter->next;
        }
    }
    return head;
}

float srednee(struct node_t *head, int *n)
{
    float sum = 0;
    while (head)
    {
        sum+=head->num;
        head = head->next;
        (*n)++;
    }
    return sum;
}

struct node_t* oper_del(struct node_t *head, float sum)
{
    struct node_t *iter = head, *new = NULL, *node;
    while (iter)
    {
        if (iter->num - sum < EPS)
        {
            node = list_create(iter->num);
            new = list_add_end(new, node);
        }
        iter = iter->next;
    }
    return new;
}
