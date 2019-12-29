#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Константа показывающая что все верно
#define OK 0

//Константа вызывающаяся если указатель не был верно перемещен на нужную позицию
#define ERROR -1

//Константа показывающая что введен неправильный режим работы с бинарным файлом
#define ERR -2

//Константа показывающая что не удалось открыть файл
#define ERR_OPEN -3

//Константа показывающая что произошла ошибка с вводом
#define ERR_PROCESS -4


/*Функция показывающая с какими режимами может работать пользователь*/
void usage(void)
{
    printf("main.exe <action>\n");
    printf("action\n");
    printf("c_create_bin_file\n");
    printf("p_print_bin_file\n");
    printf("s_sort_bin_file\n");
}

/* Функция которя считывает число с файла по заданной позиции.
Принимает файл, текущую позицию, и переменную в которую запишется число.
Возвращает функция код ошибки*/

int get_number_by_pos(FILE *f, int *num, int pos)
{
    int status = OK;
    pos *= sizeof(int);
    if (fseek(f, pos, SEEK_SET) != 0)
        status = ERROR;
    else
    {
        if (fread(num, sizeof(int), 1, f) != 1)
            status = ERR_PROCESS;
    }
    return status;
}

/* Функция которя записывает число в файл по заданной позиции.
Принимает файл, текущую позицию, и переменную в которую запишется число.
Возвращает функция код ошибки*/

int put_number_by_pos(FILE *f, int *num, int pos)
{
    int status = OK;
    pos *= sizeof(int);
    if (fseek(f, pos, SEEK_SET) != 0)
        status = ERROR;
    else
    {
        if (fwrite(num, sizeof(int), 1, f) != 1)
            status = ERR_PROCESS;
    }
    return status;
}

/*Функция сортировки элементов файла. Принимает сам файл, возвращает код ошибки*/

/*int sort(FILE *f, int size)
{
    int num1, num2, status = OK;
    for (int i = 0; (i < size - 1) && status == OK; i++)
    {
        for (int j = 0; (j < size - i - 1) && status == OK; j++)
        {
            status = get_number_by_pos(f, &num1, j);
            if (status == OK)
            {
                status = get_number_by_pos(f, &num2, j + 1);
                if (status == OK)
                {
                    if (num1 > num2)
                    {
                        status = put_number_by_pos(f, &num2, j);
                        if (status == OK)
                        {
                            status = put_number_by_pos(f, &num1, j + 1);
                            if (status != OK)
                                return status;
                        }
                        else
                            return status;
                    }
                }
                else
                    return status;
            }
            else
                return status;
        }
    }
    return status;
}*/

//Сортировка выбором
int sort(FILE *f, int size)
{
    int num1, num2, status = OK, indexmin;
    for (int i = 0; (i < size) && status == OK; i++)
    {
        indexmin = i;
        for (int j = i + 1; (j < size) && status == OK; j++)
        {
            if (get_number_by_pos(f, &num1, j) == OK)
            {
                if (get_number_by_pos(f, &num2, indexmin) == OK)
                {
                    if (num1 < num2)
                        indexmin = j;
                }
                else
                    return ERROR;;
            }
            else
                return ERROR;
        }
        if (get_number_by_pos(f, &num1, i) != OK)
            return ERROR;
        if (get_number_by_pos(f, &num2, indexmin) != OK)
            return ERROR;
        if (put_number_by_pos(f, &num1, indexmin) != OK)
            return ERROR;
        if (put_number_by_pos(f, &num2, i) != OK)
            return ERROR;
    }
    return status;
}

/*Функция которая создает файл и заполняет его рандомными числами от 0 до 200.
Принимает файл, возвращает код ошибки*/
int create(FILE *f)
{
    int number, status = OK;
    long int size;
    srand(time(NULL));
    size = rand() % 1000;
    if (fseek(f, 0, SEEK_SET) != 0)
        status = ERR_PROCESS;
    else
    {
        for (long i = 0; (i < size) && status == OK; i++)
        {
            number = rand() % 200;
            if (fwrite(&number, sizeof(int), 1, f) != 1)
                status = ERR_PROCESS;
        }
    }
    return status;
}
 /*Функция которая печатает содержимое файла. Принимает файл, возвращает код ошибки*/
int print_bin_file(FILE *f)
{
    int number, status = OK, value;
    if (fseek(f, 0, SEEK_END) != 0)
        status = ERR_PROCESS;
    else
    {
        value = ftell(f) / sizeof(int);
        if (value > 0)
        {
            if (fseek(f, 0, SEEK_SET) != 0)
                status = ERR_PROCESS;
            else
            {
                for (int i = 0; (i < value) && status == OK; i++)
                {
                    if (fread(&number, sizeof(int), 1, f) == 1)
                        printf("%d ", number);
                    else
                        status = ERR_PROCESS;
                }
            }
        }
        else
            status = ERROR;
    }
    return status;
}

/*Режим сортировки файла. Вызывает в себе функцию sort для сортировки*/
int sort_file(FILE *f)
{
    int value, status = OK;
    if (fseek(f, 0, SEEK_END) != 0)
        status = ERR_PROCESS;
    else
    {
        value = ftell(f) / sizeof(int);
        if (value > 0)
        {
            if (fseek(f, 0, SEEK_SET) != 0)
                status = ERR_PROCESS;
            else
                status = sort(f, value);
        }
        else
            status = ERROR;
    }
    return status;
}

int main(int argc, char *argv[])
{
    FILE *f = NULL;
    int rc = OK;
    if (argc != 3)
    {
        usage();
        rc = ERR;
    }
    if (strcmp(argv[1], "c") == 0)
    {
        f = fopen(argv[2], "wb");
        if (f == NULL)
        {
            printf("Can't open file which is not exist");
            rc = ERR_OPEN;
        }
        else
        {
            rc = create(f);
            if (rc == ERR_PROCESS)
            {
                printf("Failed on writing in file\n");
                fclose(f);
            }
            else
                fclose(f);
        }
    }
    else if (strcmp(argv[1], "p") == 0)
    {
        f = fopen(argv[2], "rb");
        if (f == NULL)
        {
            printf("Can't open file which is not exist");
            rc = ERR_OPEN;
        }
        else
        {
            rc = print_bin_file(f);
            if (rc == ERR_PROCESS)
            {
                printf("Failed on writing in file\n");
                fclose(f);
            }
            else
                fclose(f);
        }
    }
    else if (strcmp(argv[1], "s") == 0)
    {
        f = fopen(argv[2], "r+b");
        if (f == NULL)
        {
            printf("Can't open file which is not exist");
            rc = ERR_OPEN;
        }
        else
        {
            rc = sort_file(f);
            if (rc == ERR_PROCESS || rc == ERROR)
            {
                printf("Failed on sorting file\n");
                fclose(f);
            }
            else
                fclose(f);
        }
    }
    else
    {
        usage();
        rc = ERR;
    }
    return rc;
}
