#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "structure.h"

/**
 * \fn struct number * list_create_node(int n, int pow)
 * \brief Функция, которая создаёт узел списка.
 * \param [in] n - простое число.
 * \param [in] pow - степень простого числа.
 * \return созданный узел.
 */

struct number *list_create_node(int n, int pow)
{
    struct number *node = malloc(sizeof(struct number));
    if (node)
    {
        node->num = n;
        node->power = pow;
        node->next = NULL;
    }
    return node;
}

/**
 * \fn struct number *list_add_end(struct number *head, struct number *node)
 * \brief Функция, которая вставляет узел в конец списка.
 * \param [in] number *head - указатель на голову списка.
 * \param [in] number *node - вставляемый узел.
 * \return указатель вставленный узел.
 */

struct number *list_add_end(struct number *head, struct number *node)
{
    if (!head)
        return node;
    struct number *iter = head;
    while (iter->next)
        iter = iter->next;    
    iter->next = node;
    return head;
}

/**
 * \fn struct number *list_add_begin(struct number *head, struct number *node)
 * \brief Функция, которая вставляет узел в начало списка.
 * \param [in] number *head - указатель на голову списка.
 * \param [in] number *node - вставляемый узел.
 * \return указатель вставленный узел.
 */

struct number *list_add_begin(struct number *head, struct number *node)
{
    node->next = head;
    return node;
}

/**
 * \fn list_print(struct number *head)
 * \brief Функция, которая печатает список.
 * \param [in] number *head - указатель на голову списка.
 */

void list_print(struct number *head)
{
    struct number *iter = head;
    while (iter)
    {
        printf("%d %d ", iter->num, iter->power);
        iter = iter->next;
    }
    printf("1\n");
}

/**
 * \fn list_free(struct number *head)
 * \brief Функция, освобождающая память из под списка.
 * \param [in] number *head - указатель на голову списка.
 */

void list_free(struct number *head)
{
    struct number *iter = head, *del = NULL;
    while (iter)
    {
        del = iter;
        iter = iter->next;
        free(del);
    }
}

/**
 * \fn list_inverse(struct number **head)
 * \brief Функция, переварачивающая список наоборот.
 * \param [in] number *head - указатель на голову списка.
 */

void list_inverse(struct number **head)
{
    struct number *cur = *head, *new = NULL, *node;
    while (cur)
    {
        node = cur;
        cur = cur->next;
        node->next = NULL;
        new = list_add_begin(new, node);
    }
    *head = new;
}