#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define TITTLE_LEN 30
#define PRODUCER 15
#define ERR_IO -1
#define ERR -2
#define ERR_MEM -3
#define ERR_SIZE -4
#define ERR_PARAM 53
#define OK 0
//максимальное число товаров
#define N_MAX 10

/* Эта структура представляет собой 4 переменных разного типа.
 * В переменную name записывается название товара
 * В переменную manufacturer записывается производитель товара
 * Переменные price и quantity имеют тип безнаковое целое длиной 32 бита.
 * В эти переменные записываются цена и количество товара соответственно*/

struct product
{
    char name[TITTLE_LEN + 1];
    char manufacturer[PRODUCER + 1];
    uint32_t price;
    uint32_t quantity;
};

/*Функция которая считывает данные об одном товаре с файла и записывает их в структуру*/
int read_product_info(FILE *f, struct product *current_product)
{
    char buf[8];
    int len;
    if (!fgets(current_product->name, sizeof(current_product->name), f))
        return ERR_IO;
    len = strlen(current_product->name);
    if (current_product->name[len - 1] == '\n')
        current_product->name[len - 1] = '\0';
    if (!fgets(current_product->manufacturer, sizeof(current_product->manufacturer), f))
        return ERR_IO;
    len = strlen(current_product->manufacturer);
    if (current_product->manufacturer[len - 1] == '\n')
        current_product->manufacturer[len - 1] = '\0';
    if (fscanf(f, "%u%u", &current_product->price, &current_product->quantity) != 2)
        return ERR_IO;
    fgets(buf, sizeof(buf),f);
    return OK;
}

/*Функция которая помещает структуру в массив, то есть каждую информацию о товаре.
 * Принимает файл, структуру и число товаров*/
int read_product_array(FILE *f, struct product *arr, int *n)
{
    struct product current_product;
    int k = 0, rc = OK;
    while (rc == OK)
    {
        rc = read_product_info(f, &current_product);
        if (rc == OK)
        {
            if (k < N_MAX)
            {
                arr[k] = current_product;
                k++;
            }
            else
                rc = ERR;
        }
        (*n) = k;
    }
    if (rc != ERR_MEM)
        rc = OK;
    return rc;
}

/*Выводит информацию об одном товаре*/
void print_product_info(const struct product *data)
{
    printf("%s\n", data->name);
    printf("%s\n", data->manufacturer);
    printf("%u\n", data->price);
    printf("%u\n", data->quantity);
}

/*Функция проверяет сравнивает последние символы названия товара с введенными данными.
 * Для сравнения использутся переменная k. Сравнивание начинается с последнего символа.
 * Возвращает 1 при успешном выполнении иначе 0. */
int check(const struct product *arr, const char *mark)
{
    int flag = 1, k = 1, lenght = strlen(mark);
    while (flag && lenght > 0)
    {
        if (strcmp(&arr->name[strlen(arr->name) - k], &mark[strlen(mark) - k]) == 0)
        {
            k++;
            lenght--;
        }
        else
            flag = 0;
    }
    return flag;
}

/*Функция которая считает каждую структуру в массиве, в которой будет выполняется условие функции check.
 * Принимает структуру, количество товаров, и строку введенной в коммандной строке*/
int count_product_array(const struct product *arr, int n, char *mark)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (check(&arr[i], mark))
            count++;
    }
    return count;
}

int main(int argc, char *argv[])
{
    FILE *f = NULL;
    struct product arr[N_MAX];
    int n, rc = OK;
    char mark[TITTLE_LEN+1];
    if (argc != 4)
        rc = ERR_PARAM;
    if (rc == OK)
    {
        if (strcmp(argv[1], "ft") == 0)
        {
            f = fopen(argv[2], "r");
            if (f == NULL)
            {
                printf("Can't open file\n");
                rc = ERR;
            }
            else
            {
                fseek(f, 0, SEEK_END);
                if (ftell(f) != 0)
                {
                    fseek(f, 0, SEEK_SET);
                    strcpy(mark, argv[3]);
                    rc = read_product_array(f, arr, &n);
                    if (rc == OK)
                    {
                        if (count_product_array(arr, n, mark) != 0)
                        {
                            for (int i = 0; i < n; i++)
                            {
                                if (check(&arr[i], mark))
                                    print_product_info(&arr[i]);
                            }
                        }
                        else
                            rc = ERR;
                    }
                }
                else
                    rc = ERR_SIZE;
            }
            fclose(f);
        }
        else
            rc = ERR_PARAM;
    }
    return rc;
}
