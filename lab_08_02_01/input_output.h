#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

int input_elements(double *pcur, double *pend);
int input(double **parr, double **pend, int *n);
void print(const double *parr, const double *pend);
void print_errors(int rc);

#endif // INPUT_OUTPUT_H
