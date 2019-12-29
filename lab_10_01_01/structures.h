#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct
{
    int year;
    int month;
    int day;
}birthdate;

typedef struct
{
    char *surname;
    char *sex;
    birthdate date;
    int num_grades;
    int *grades;
}pupil;

typedef struct
{
    pupil **data;
    int len;
    int allocated;
}pupil_arr;

#endif // STRUCTURES_H
