#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "in_out.h"
#include "operations.h"
#include "constants.h"
#include "structure.h"


/**
 * \fn create_node_and_add_list(struct number **list, int number, int power)
 * \brief Функция, которая создает узел и добавляет его в список.
 * \param [in] list - список.
 * \param [in] number - добавляемое число.
 * \param [in] power - степень добавляемого числа.
 * \return код ошибки.
 */

int create_node_and_add_list(struct number **list, int number, int power)
{
    struct number *node;
    node = list_create_node(number, power);
    if (!node)
        return ERR_MEMORY;
    *list = list_add_end(*list, node);
    return OK;
}

/**
 * \fn reallocate(int **arr, int n)
 * \brief Функция, перевыделяет память для массива из простых множителей числа.
 * \param [in] arr - массив.
 * \param [in] n - новый размер массива.
 * \return код ошибки.
 */

int reallocate(int **arr, int n)
{
    int *new = NULL;

    new = realloc(*arr, sizeof(int) * n);
    if (new)
    {
        *arr = new;
        new = NULL;
    }
    else
        return ERR_MEMORY;
    return OK;
}

/**
 * \fn check_prime_num(int n)
 * \brief Функция, которая проверяет является ли число простым.
 * \param [in] n - проверяемое число.
 * \return результат проверки.
 */

bool check_prime_num(int n)
{
    if (n > 1)
    {
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
                return false;
        }
    }
    else
        return false;
    return true;
}

/**
 * \fn break_up_num(int num, int **arr, int *k)
 * \brief Функция, разбивающая число на простые числа.
 * \param [in] arr - массив.
 * \param [in] num - разбиваемое число.
 * \return код ошибки.
 */

int break_up_num(int num, int **arr, int *k)
{
    int i = 1;
    int rc = OK;

    while (i <= num && rc == OK)
    {
        if (check_prime_num(i) == true)
        {
            if (num % i == 0)
            {
                num = num / i;
                (*arr)[*k] = i;
                (*k)++;
                rc = reallocate(arr, *k + 1);
                i = 1;
            }
            else
                i++;
        }
        else
            i++;
    }
    return rc;
}

/**
 * \fn count_and_input_pow(int *arr, struct number **list, int k)
 * \brief Функция, считающая степень каждого простого множителя.
 * \param [in] arr - массив.
 * \param [in] number **list - список.
 * \param [in] k - размер массива.
 * \return код ошибки.
 */

int count_and_input_pow(int *arr, struct number **list, int k)
{
    int count = 1;
    int rc;
    for (int i = 0; i < k - 1; i++)
    {
        if (arr[i] == arr[i + 1])
            count++;
        else
        {
            rc = create_node_and_add_list(list, arr[i], count);
            if (rc != OK)
                return rc;
            count = 1;
        }
    }
    rc = create_node_and_add_list(list, arr[k - 1], count);
    if (rc != OK)
        return rc;
    return rc;
}

/**
 * \fn multiplier_divider(int n, struct number **list)
 * \brief Функция, делящая число на простые множители и добавляющее его в список.
 * \param [in] n - разбиваемое число.
 * \param [in] number **list - список.
 * \return rc - код ошибки.
 */

int multiplier_divider(int n, struct number **list)
{
    int rc = OK;
    int k = 0;
    int *arr = NULL;

    arr = malloc(sizeof(int));
    if (!arr)
        rc = ERR_MEMORY;
    if (rc == OK)
    {
        rc = break_up_num(n, &arr, &k);
        if (rc == OK)
            rc = count_and_input_pow(arr, list, k);
        free(arr);
    }
    return rc;
}

/**
 * \fn choose_key(char *key)
 * \brief Функция, которая по введенному ключу вызывает соответствующую операцию.
 * \param [in] n - введенный ключ.
 * \return rc - код ошибки.
 */

int choose_key(char *key)
{
    int rc;
    int flag = 0;
    if (strcmp(key, "out") == 0)
    {
        flag = 1;
        rc = out();
    }
    if (strcmp(key, "mul") == 0)
    {
        flag = 1;
        rc = mul();
    }
    if (strcmp(key, "sqr") == 0)
    {
        flag = 1;
        rc = sqr();
    }
    if (strcmp(key, "div") == 0)
    {
        flag = 1;
        rc = division();
    }
    if (flag == 0)
        rc = ERR_INPUT;
    return rc;
}

/**
 * \fn list_find_equal(struct number *head, int what)
 * \brief Функция, которая ищет идентичный элемент в списке.
 * \param [in] what - искомый элемент.
 * \return указатель на голову.
 */

struct number *list_find_equal(struct number *head, int what)
{
    while (head && head->num != what)
        head = head->next;
    return head;
}

/**
 * \fn list_find_less(struct number *head, int what)
 * \brief Функция, которая ищет элемент меньше проверяемого элемента в списке.
 * \param [in] what - искомый элемент.
 * \return указатель на голову.
 */

struct number *list_find_less(struct number *head, int what)
{
    while (head && head->num < what)
        head = head->next;
    return head;
}