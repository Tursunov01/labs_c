#ifndef __CDIO__LIB__H__

#define __CDIO__LIB__H__

#define OK 0 
#define ERR_INPUT -1
#define ERR_RANGE -2
#define ERR_ALLOCATION -3
#define EMPTY_ARRAY -4 
#define ERR_LEN -5
#define ERR_SIZE -6 

void arr_free(double *pcur);

int input_elements(double *pcur, double *pend);

int input(double **parr, double **pend, int *n);

void print(const double *parr, const double *pend);

void print_errors(int rc);

void move_left(double *pcur, double *pend);

void move_right(double *pcur, double *pend);

int delete(double *parr, double **pend);

int insert(double **parr, double **pend, int p, double m2);

double average(const double *parr, const double *pend);

double find_max(const double *parr, const double *pend);

int reallocate(double **parr, double **pend, int n);

#endif  // __CDIO__LIB__H__