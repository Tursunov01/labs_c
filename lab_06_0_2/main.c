#include <stdio.h>
#include <string.h>

// Константа для максимального размера строки
#define MAX_LEN 256

//Константа для максимальной длины подстроки
#define LEN_WORD 16

//Константа которая сообщает что все правильно
#define OK 0;

//Код ошибки вызывающийся при переполнении
#define ERR_INPUT -1

//Константа используется если сделан неправильный ввод строки
#define ERR_GET -2

// Константа используемая при переполнении
#define ERR_COVER -3

// Константа используемая если в строке нет ни одного слова или происходит переполнение матрицы
#define ERR_NO_WORD -4

// Константа используемая если слово превышает 16 символов
#define ERR_WORD -5

#define TRUE 1

#define FALSE 0

/*Функция которая проверяет символ на разделитель*/
/*int separator(char symbol)
{
    if (symbol == ' ' || symbol == '.' || symbol == ',' || symbol == ':' || symbol == ';' ||
        symbol == '-' || symbol == '?' || symbol == '!')
        return 1;
    return 0;
}*/

/*Функция которая проверяет символ на разделитель*/
int separator(char symbol)
{
    char spacers[] = " .,:;-?!";
    if (strchr(spacers, symbol) != NULL)
        return 1;
    return 0;
}

/*Функция которая находит начальную и конечную позицию текущего слова. Если выполнены все условия,
то возвращает TRUE, иначе FALSE*/
int get_word_pos(const char *str, int *ibeg, int *iend)
{
    int i = (*ibeg);
    while (str[i] && separator(str[i]))
        i++;
    if (str[i])
    {
        (*ibeg) = i;
        while (str[i] && !separator(str[i]))
            i++;
        (*iend) = i - 1;
        return TRUE;
    }
    return FALSE;
}

/*Функция в которую передается слово, которое она проверяет на существование в массиве уникальных слов.
 * Если такое слово уже есть в массиве, то счётчик который считает колчество встреч этих слов увеличивается на 1.
 * Иначе если этого слова нет в массиве, то он добавляется в массив и счётчик становитс равным 1.*/
void check_and_calc_count(char matrix[][LEN_WORD + 1], int *array, char *current_word, int *pos)
{
    int flag = 0;
    flag = 0;
    for (int i = 0; i < (*pos); i++)
    {
        if (strcmp((matrix[i]), current_word) == 0)
        {
            flag = 1;
            array[i]++;
        }
    }
    if (flag == 0)
    {
        for (int j = 0; j < strlen(current_word); j++)
        {
            matrix[*pos][j] = current_word[j];
        }
        matrix[*pos][strlen(current_word)] = '\0';
        array[*pos] = 1;
        (*pos)++;
    }
}

/*Функция которая формирует слово и вызывает в себе функцию check_and_calc_count, в которой формируется массив слов.
Что сформировать слово используется функция get_word_pos.Вовращает количество слов*/
int forming(char *str, char matrix[][LEN_WORD + 1], int *array)
{
    int ibeg = 0, iend = 0, pos = 0, k = 0, flag = 0;
    char current_word[LEN_WORD];
    while (get_word_pos(str, &ibeg, &iend))
    {
        k = 0;
        for (int i = ibeg; i <= iend; i++)
        {
            current_word[k] = str[i];
            k++;
        }
        current_word[k] = '\0';
        if (k > LEN_WORD)
        {
            flag = 1;
            return ERR_WORD;
        }
        if (flag == 0)
        {
            check_and_calc_count(matrix, array, current_word, &pos);
            ibeg = iend + 1;
        }
    }
    return pos;
}


int main(void)
{
    char str[MAX_LEN + 1];
    char matrix[MAX_LEN / 2][LEN_WORD + 1];
    int array[MAX_LEN / 2];
    int rows, rc = OK;
    setbuf(stdout, NULL);
    printf("Input string: ");
    if (fgets(str, MAX_LEN + 1, stdin) != NULL)
    {
        if (str[strlen(str) - 1] == '\n')
        {
            str[strlen(str) - 1] = '\0';
            if (strlen(str) != 0)
            {
                rows = forming(str, matrix, array);
                if (rows == ERR_WORD)
                    rc = ERR_WORD;
                else
                {
                    if (rows > 0 && rows <= (MAX_LEN / 2))
                    {
                        printf("Result:\n");
                        for (int i = 0; i < rows; i++)
                            printf("%s %d\n", matrix[i], array[i]);
                    }
                    else
                        rc = ERR_NO_WORD;
                }
            }
            else
                rc = ERR_GET;
        }
        else
            rc = ERR_COVER;
    }
    else
        rc = ERR_GET;
    return rc;
}
