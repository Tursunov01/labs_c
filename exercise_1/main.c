#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Константа показывающая что все верно
#define OK 0

//Константа показывающая что введено неправильное количество параметров командной строки
#define ERR_WRONG_CMD 1

//Код ошибки если невозможно открыть файл
#define ERR_IO 2

//Код ошибки в которой не получилось вычислить среднее арифметическое мин и макс элемента*/
#define NO_RESULT 3

//Код ошибки если не получилось усатановить указатель на нужную позицию
#define ERR_POS 4

#define MAX 128



int check_and_put(FILE *f, FILE *f1,char *str, int number)
{
    int status = NO_RESULT, count = 0;;
    char current[MAX];
    while (fgets(current, sizeof(current), f) != NULL)
   {
        status = OK;
        count++;
        fprintf(f1, current);
        if (count == number)
            fprintf(f1,str);
    }
    if (number > count )
        status = ERR_IO;
    return status;
}


/*int main(int argc, char *argv[])
{
    FILE *f = NULL;
    FILE *f1 = NULL;
    char str[MAX + 1];
    int rc = OK, position;
    printf("Input str: ");
    if (fgets(str, 128, stdin) == NULL)
        rc = ERR_IO;
    else
    {
        printf("Input position: ");
        if (scanf("%d", &position) != 1)
            rc = ERR_IO;
        else
        {
            if (argc != 3)
            {
                printf("main.exe test\n");
                return ERR_WRONG_CMD;
            }
            f = fopen(argv[1], "r");
            f1 = fopen(argv[2], "w");
            if (f)
            {
                if (f1)
                {
                    rc = check_and_put(f, f1 ,str, position);
                    fclose(f);
                    fclose(f1);
                }
                else
                {
                    printf("Can't open file\n");
                    rc = ERR_IO;
                }
            }
            else
            {
                printf("Can't open file\n");
                rc = ERR_IO;
            }
        }
    }
    return rc;
}*/


int main(int argc, char *argv[])
{
    FILE *f = NULL;
    FILE *f1 = NULL;
    char str[MAX + 1];
    int rc = OK, position;
    if (argc != 5)
    {
        printf("main.exe test\n");
        rc = ERR_WRONG_CMD;
    }
    if (rc == OK)
    {
        f = fopen(argv[1], "r");
        if (f)
        {
            f1 = fopen(argv[2], "w");
            if (f1)
            {
                if (strlen(argv[4]) <= MAX)
                {
                    strcpy(str, argv[4]);
                    position = atoi(argv[3]);
                    if (position > 0)
                    {
                        str[strlen(str)] = '\n';
                        rc = check_and_put(f, f1 ,str, position);
                        fclose(f1);
                    }
                    else
                        rc = ERR_IO;
                }
                    else
                    rc = ERR_IO;
            }
            else
            {
                printf("Can't open file\n");
                rc = ERR_IO;
            }
            fclose(f);
        }
        else
        {
            printf("Can't open file\n");
            rc = ERR_IO;
        }
    }
    return rc;
}
