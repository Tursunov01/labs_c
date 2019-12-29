#ifndef SECONDARY_FUNCTIONS_H
#define SECONDARY_FUNCTIONS_H

double average(const double *parr, const double *pend);
double find_max(const double *parr, const double *pend);
void move_left(const double *pcur, const double *pend);
void move_right(const double *pcur, const double *pend);
int reallocate(double **parr, double **pend, int n);

#endif // SECONDARY_FUNCTIONS_H
