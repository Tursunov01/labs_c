#include <stdio.h>
#include <stdlib.h>

#include "in_out.h"
#include "func.h"
#include "operations.h"
#include "constants.h"
#include "structure.h"

/**
 * \fn operation(struct number *list1, struct number *list2, struct number **list3, char sign)
 * \brief Функция, которая выполняет операцию умножения, деления.
 * \param [in] list1 - список в котором множители первого числа.
 * \param [in] list2 - список в котором множители второго числа.
 * \param [in] list3 - список в котором хранится множители результата.
 * \param [in] sign - знак определяющий выполняемую операцию(умножение/деление).
 * \return rc - код ошибки.
 */

int operation(struct number *list1, struct number *list2, struct number **list3, char sign)
{
    struct number *cur1 = list1, *cur2 = list2, *cur3 = NULL;
    int rc = OK;
    while (cur1 && cur2)
    {
        cur3 = list_find_equal(cur2, cur1->num);
        //если найден идентичный
        if (cur3 != NULL)
        {
            if (sign == '*')
                rc = create_node_and_add_list(list3, cur3->num, cur3->power + cur1->power);
            if (sign == '/')
            {
                if (cur3->power - cur1->power != 0)
                    rc = create_node_and_add_list(list3, cur3->num, cur1->power - cur3->power);
            }
            if (rc != OK)
                return rc;
            cur1 = cur1->next;
            cur2 = cur2->next;
            rc = PASS;
        }
        if (rc == OK)
        {
            //если cur1->num < cur2->num
            cur3 = list_find_less(cur2, cur1->num);
            if (cur3 != NULL)
            {
                rc = create_node_and_add_list(list3, cur1->num, cur1->power);
                if (rc != OK)
                    return rc;
                cur1 = cur1->next;
                rc = PASS;
            }
        }
        //это условие для того чтобы проверить найден ли такой элемент из list1, который <= элменту из list2
        if (rc == PASS)
            rc = OK;
        else
            break;
    }
    if (cur2 != NULL)
    {
        while (cur2 != NULL)
        {
            rc = create_node_and_add_list(list3, cur2->num, cur2->power);
            if (rc != OK)
                return rc;
            cur2 = cur2->next;
        }
    }
    if (cur1 != NULL)
    {
        while (cur1 != NULL)
        {
            rc = create_node_and_add_list(list3, cur1->num, cur1->power);
            if (rc != OK)
                return rc;
            cur1 = cur1->next;
        }
    }
    return rc;
}

/**
 * \fn out(void)
 * \brief Функция вывода множителей, введенного числа.
 * \return rc - код ошибки.
 */

int out(void)
{
    int n;
    int rc = OK;
    struct number *list = NULL;

    //printf("Input first number: ");
    if (scanf("%d", &n) != 1)
        return ERR_INPUT;
    if (n <= 1)
        return ERR_RANGE;
    rc = multiplier_divider(n, &list);
    if (rc == OK)
    {
        list_inverse(&list);
        list_print(list);
    }
    list_free(list);
    return rc;
}

/**
 * \fn mul(void)
 * \brief Функция умножения 2 чисел предствленных ввиде списка.
 * \return rc - код ошибки.
 */

int mul(void)
{
    int n, m;
    int rc = OK;
    struct number *list1 = NULL, *list2 = NULL, *list3 = NULL; 

    //printf("Input first number: ");
    if (scanf("%d", &n) != 1)
        return ERR_INPUT;
    if (n <= 1)
        return ERR_RANGE;
    //printf("Input second number: ");
    if (scanf("%d", &m) != 1)
        return ERR_INPUT;
    if (m <= 1)
        return ERR_RANGE;
    rc = multiplier_divider(n, &list1);
    if (rc == OK)
    {
        rc = multiplier_divider(m, &list2);
        if (rc == OK)
        {
            if (n >= m)
                rc = operation(list1, list2, &list3, '*');
            if (m > n)
                rc = operation(list2, list1, &list3, '*');
            if (rc == OK)
            {
                list_inverse(&list3);
                list_print(list3);
            }
        }
    }
    list_free(list1);
    list_free(list2);
    list_free(list3);
    return rc;
}

/**
 * \fn sqr(void)
 * \brief Функция ведения числа предствленного ввиде списка.
 * \return rc - код ошибки.
 */

int sqr(void)
{
    int n;
    int rc = OK;
    struct number *list1 = NULL, *list2 = NULL;

    //printf("Input first number: ");
    if (scanf("%d", &n) != 1)
        return ERR_INPUT;
    if (n <= 1)
        return ERR_RANGE;
    rc = multiplier_divider(n, &list1);
    if (rc == OK)
    {
        rc = operation(list1, list1, &list2, '*');
        if (rc == OK)
        {
            list_inverse(&list2);
            list_print(list2);
        }
    }
    list_free(list1);
    list_free(list2);
    return rc;
}

/**
 * \fn division(void)
 * \brief Функция деления 2 чисел предствленных ввиде списка.
 * \return rc - код ошибки.
 */

int division(void)
{
    int n, m;
    int rc = OK;
    struct number *list1 = NULL, *list2 = NULL, *list3 = NULL;

    //printf("Input first number: ");
    if (scanf("%d", &n) != 1)
        return ERR_INPUT;
    if (n <= 1)
        return ERR_RANGE;
    //printf("Input second number: ");
    if (scanf("%d", &m) != 1)
        return ERR_INPUT;
    if (m <= 1)
        return ERR_RANGE;
    if (n % m != 0)
        return ERR_DIV;
    rc = multiplier_divider(n, &list1);
    if (rc == OK)
    {
        rc = multiplier_divider(m, &list2);
        if (rc == OK)
        {
            rc = operation(list1, list2, &list3, '/');
            if (rc == OK)
            {
                list_inverse(&list3);
                list_print(list3);
            }
        }
    }
    list_free(list1);
    list_free(list2);
    list_free(list3);
    return rc;
}
