#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "constants.h"
#include "structures.h"
#include "func.h"
#include "in_out.h"

/**
 * \fn input_and_check_for_overflow(const char *str)
 * \brief Функция, которая присваевает веденное значение в текущую переменную  и проверяет ее на переполнение
 * \param [in] str - строка, в которую запишутся данные
 */

int input_and_check_for_overflow(char *str)
{
    if (!fgets(str, MAX_LEN, stdin))
        return ERR_INPUT;
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    else
        return ERR_OVERFLOW;
    return OK;
}

/**
 * \fn input_arr_grades(int num_grades, int *grades)
 * \brief Функция, для ввода количества и сами оценки ученика
 * \param [in] num_grades - количество оценок
 * \param [in] grades - массив оценок
 */

int input_arr_grades(int *num_grades, int *grades)
{
    if (scanf("%d", num_grades) != 1)
        return ERR_INPUT;
    if (*num_grades < 0)
        return ERR_INPUT;
    for (int i = 0; i < *num_grades; i++)
    {
        if (scanf("%d", grades + i) != 1)
            return ERR_INPUT;
        if (grades[i] < 0)
            return ERR_RANGE;
    }
    return OK;
}

/**
 * \fn pupil_free(pupil *current)
 * \brief Функция, которая освождает память из под записи
 * \param [in] current - запись
 */


void pupil_free(pupil *current)
{
    if (current->grades)
        free(current->grades);
    if (current->sex)
        free(current->sex);
    if (current->surname)
        free(current->surname);
    if (current)
        free(current);
}

/**
 * \fn pupil* pupil_create(const char *surname, const char *sex, const char *birthday, int *grades)
 * \brief Функция, которая выделяет память для каждого поля записи и записывает туда соответствующие данные
 * \param [in] surname - записываемая фамилия
 * \param [in] sex - записываемый пол
 * \param [in] birthday - записываемая дата рождения
 * \param [in] grades - записываемые оценки за последнюю четверть
 * \return - код ошибки
 */


/*Первая ошибка заключалась в моей невнимательности, то есть в описании функций "pupil create"
 * в in_out.c и in_out.h отличались. А отличие было в переменной "birthdate cur", которая была написана в in_out.h
 * как "birthdate *cur". Компилятор на виндовс не уследил эту ошибку, но компилятор на ubuntu сделал это.
 * Следующая ошибка в модульных тестах. (см test_system.c строка 159)*/
pupil*pupil_create(const char *surname, const char *sex, birthdate cur, int num_grades, int *grades)
{
    pupil *current;
    current = malloc(sizeof(pupil));
    if (!current)
        return NULL;

    current->surname = malloc((strlen(surname) + 1) * sizeof(char));
    if (!current->surname)
    {
        pupil_free(current);
        return NULL;
    }
    strcpy(current->surname, surname);

    current->sex = malloc((strlen(sex) + 1) * sizeof(char));
    if (!current->sex)
    {
        pupil_free(current);
        return NULL;
    }
    strcpy(current->sex, sex);

    current->date.year = cur.year;
    current->date.month = cur.month;
    current->date.day = cur.day;

    current->num_grades = num_grades;
    current->grades = malloc((num_grades) * sizeof(int));
    if (!current->grades)
    {
        pupil_free(current);
        return NULL;
    }
    for (int i = 0; i < num_grades; i++)
        current->grades[i] = grades[i];

    return current;
}

/**
 * \fn pupil_input(pupil **current)
 * \brief Функция, предназначенная для ввода данных для текущей записи
 * \param [in] current - вводимая запись
 * \return - код ошибки
 */

int pupil_input(pupil **current)
{
    char surname[MAX_LEN];
    char sex[MAX_LEN];
    char birthday[MAX_LEN];
    int grades[MAX_LEN];
    int num_grades;
    birthdate cur;
    int rc;
    printf("Input surname of pupil: ");
    rc = input_and_check_for_overflow(surname);
    if (rc != OK)
        return rc;
    if (check_surname(surname) == ERR_INPUT)
        return ERR_INPUT;
    if (cmp_case_insentive(surname, "nobody") == 0)
        return ERR_STOP;
    printf("Input sex of pupil: ");
    rc = input_and_check_for_overflow(sex);
    if (rc != OK)
        return rc;
    if (cmp_case_insentive(sex, "male") != 0 && cmp_case_insentive(sex, "female") != 0)
        return ERR_INPUT;
    printf("Input birthday of pupil: ");
    rc = input_and_check_for_overflow(birthday);
    if (rc != OK)
        return rc;
    if (check_birthday(birthday, &cur) != OK)
        return ERR_INPUT;
    printf("Input number of grades and grades of pupil: ");
    rc = input_arr_grades(&num_grades, grades);
    if (rc != OK)
        return rc;
    *current = pupil_create(surname, sex, cur, num_grades, grades);
    if (!current)
        return ERR_MEMORY;
    fgets(surname, sizeof(surname), stdin);
    return OK;
}

/**
 * \fn pupil_print(FILE *f, const pupil *current)
 * \brief Функция, которая записывает все поля записи в файл.
 * \param [in] current - запись
 * \param [in] f - файловая переменная
 */

void pupil_print(FILE *f, const pupil *current)
{
    fprintf(f, "%s\n", current->surname);
    fprintf(f, "%s\n", current->sex);
    fprintf(f, "%04d.%02d.%02d\n", current->date.year, current->date.month, current->date.day);
    fprintf(f, "%d ", current->num_grades);
    for (int i = 0; i < current->num_grades; i++)
        fprintf(f, "%d ", current->grades[i]);
    fprintf(f, "\n");
}
