#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "ui.h"

#define OK 0 //константа показывающая что всё верно
#define ERR_INPUT 1 // код ошибки показывающий ошибку ввода
#define ERR_RANGE 2 // код ошибки показывающий что введенный параметр выходит за определенный диапозон
#define ERR_ALLOCATION 3 // константа показывающая ошибку перевыделения памяти для массива
#define EMPTY_ARRAY 4 // константа показывающая что сформированный массив - пустой
#define ERR_LEN 5 //константа показывающая что позиция для вставки не входит в допустимый диапозон
#define ERR_SIZE 6 //код ошибки показывающий, что ввод количества элементов массива был не успешным

int input_elements(double *pcur, double *pend, char *stroka)
{
	char *pch = strtok(stroka, " ,");
	double a;
	while (pcur < pend && pch != NULL)
    {
        (*pcur) = atof(pch);
		pch = strtok(NULL, " ,");
		pcur++;
    }
    return OK;
}

/**
 * \fn input(double **parr, double **pend, int *n, int *p)
 * \brief Функция ввода количества элементов и элементов массива.
 * \param [in] parr - указатель на указатель начала массива
 * \param [in] pend - указатель на указатель конца массива
 * \param [in] n - переменная в которую запишется количество элементов
 * \return rc - код ошибки
 */
int input(double **parr, double **pend, int n, char *stroka)
{
    double *a = NULL;
    double *pcur;
    a = malloc(n * sizeof(double));
    if (a == NULL)
        return ERR_ALLOCATION;
    pcur = a;
    *pend = (a + n);
    if (input_elements(pcur, *pend, stroka) != OK)
    {
        free(a);
        return ERR_INPUT;
    }
    *parr = a;
    a = NULL;
    return OK;
}

void print(const double *parr, const double *pend)
{
    const double *pcur = parr;
    printf("Array:\n");
    while (pcur < pend)
        printf("%lf ", *pcur++);
    printf("\n");
}

double average(const double *parr, const double *pend)
{
    double sum = 0.0;
    const double *pcur;

    assert(parr != NULL);
    assert(pend != NULL);
    assert(parr < pend);

    pcur = parr;
    while (pcur < pend)
        sum += *pcur++;
    sum = sum / (pend - parr);
    return sum;
}


double find_max(const double *parr, const double *pend)
{
    const double *pcur;
    double max;

    assert(parr != NULL);
    assert(pend != NULL);
    assert(parr < pend);

    pcur = parr;
    max = *pcur;
    while (pcur < pend)
    {
        if (*pcur > max)
            max = *pcur;
        pcur++;
    }
    return max;
}


int reallocate(double **parr, double **pend, int n)
{
    double *new = NULL;

    assert(*parr != NULL);
    assert(*pend != NULL);
    assert(n > 0);

    new = realloc(*parr, sizeof(double) * n);
    if (new)
    {
        *parr = new;
        *pend = (*parr + n);
        if (parr == pend)
            return ERR_ALLOCATION;
    }
    else
        return ERR_ALLOCATION;
    return OK;
}


void move_left(double *pcur, double *pend)
{
    double *pnow;

    assert(pcur != NULL);
    assert(pend != NULL);

    pnow = pcur;
    while (pnow < pend - 1)
    {
        *pnow = *(pnow + 1);
        pnow++;
    }
}


void move_right(double *pcur, double *pend)
{
    double *pnow;

    assert(pcur != NULL);
    assert(pend != NULL);

    pnow = pend;
    while (pnow > pcur)
    {
        *pnow = *(pnow - 1);
        pnow--;
    }
}


int delete(double *parr, double **pend)
{
    double m1 = average(parr, *pend);
    double *pcur = parr, *end = *pend;
    int rc = OK;

    assert(parr != NULL);
    assert(pend != NULL);

    while (pcur < end)
    {
        if (*pcur > m1)
        {
            move_left(pcur, end);
            end--;
            pcur--;
        }
        pcur++;
    }
    *pend = end;
    if (end - parr == 0)
        return EMPTY_ARRAY;
    return rc;
}

int insert(double **parr, double **pend, int p, double m2)
{
    double *pos, *end;
    int rc;
    rc = reallocate(parr, pend, *pend - *parr + 1);
    if (rc == OK)
    {
        end = *pend - 1;
        pos = *parr + p;
        move_right(pos, end);
        *pos = m2;
    }
    return rc;
}





static uiWindow *mainwin;
uiEntry *n, *num, *p, *result;

static int onClosing(uiWindow *w, void *data)
{
	uiQuit();
	return 1;
}

static int onShouldQuit(void *data)
{
	uiWindow *mainwin = uiWindow(data);

	uiControlDestroy(uiControl(mainwin));
	return 1;
}

static void onCheckClicked(uiButton *b, void *data)
{
	char *n1, *arr, *p1, buf[100] = "", cur[100] = "";
	int size, pos;
	int rc = OK;
	double *a = NULL;
    double *end = NULL;
	double m2;
	n1 = uiEntryText(n);
	size = atoi(n1);
	if (size > 0) {
		
		arr = uiEntryText(num);
		uiEntrySetText(result, arr);
		rc = input(&a, &end, size, arr);
		if (rc == OK)
		{
			rc = delete(a, &end);
			if (rc == OK)
			{
				rc = reallocate(&a, &end, end - a);
				if (rc == OK)
				{
					p1 = uiEntryText(p);
					pos = atoi(p1);
					if (pos > 0 && pos < size && end - a > pos + 1)
					{
						m2 = find_max(a, end);
						rc = insert(&a, &end, pos, m2);
						if (rc == OK)
						{
							if (insert(&a, &end, 0, m2) == OK)
                            {
                                rc = insert(&a, &end, end - a, m2);
								if (rc == OK)
								{
									while (a < end)
									{
										int mm = snprintf(cur, 1, "%lf", *a);
										strcat(buf, cur);
										strcat(buf, " ");
										a++;
									}
									uiEntrySetText(result, buf);
									return;
								}
                            }
						}
					}
					else
					{
						uiEntrySetText(result, "input in insert in current position");
						uiEntrySetText(n, "");
						uiEntrySetText(num, "");
	    				uiEntrySetText(p, "");
						return;
					}
					
				}
			}
		}
		
	}
	else
	{
		uiEntrySetText(result, "error in size. Size must be greater than 0");
		uiEntrySetText(n, "");
		uiEntrySetText(num, "");
	    uiEntrySetText(p, "");
		return;
	}
	
	free(a);
	//uiEntrySetText(result, "input error");
	//uiEntrySetText(n, "");
	//uiEntrySetText(num, "");
	//uiEntrySetText(p, "");
	uiFreeText(n1);
	uiFreeText(p1);
	uiFreeText(arr);
}

static uiControl *makeBasicControlsPage(void)
{
	uiBox *vbox;
	uiBox *hbox;
	//uiGroup *group;
	//uiForm *entryForm;
    uiButton *button;
    
    uiGrid *grid;
	uiLabel *size, *arr_num, *pos, *res;

	vbox = uiNewVerticalBox();
	uiBoxSetPadded(vbox, 1);

	hbox = uiNewHorizontalBox();
	uiBoxSetPadded(hbox, 1);
	uiBoxAppend(vbox, uiControl(hbox), 0);

	grid = uiNewGrid();
	uiGridSetPadded(grid, 1);
	uiBoxAppend(vbox, uiControl(grid), 0);
	

	button = uiNewButton("PUSH");
	n = uiNewEntry();
	num = uiNewEntry();
	p = uiNewEntry();
	result= uiNewEntry();
	size = uiNewLabel("Input size of array");
	arr_num = uiNewLabel("Input numbers of array");
	pos = uiNewLabel("Input position of insert");
	res = uiNewLabel("Result");

	uiButtonOnClicked(button, onCheckClicked, result);
	
	uiGridAppend(grid, uiControl(button),
		0, 0, 1, 1,
		0, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(grid, uiControl(size),
		0, 1, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(grid, uiControl(n),
		0, 2, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(grid, uiControl(arr_num),
		0, 3, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(grid, uiControl(num),
		0, 4, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(grid, uiControl(pos),
		0, 5, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(grid, uiControl(p),
		0, 6, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(grid, uiControl(res),
		0, 7, 1, 1,
		1, uiAlignFill, 0, uiAlignFill);
	uiGridAppend(grid, uiControl(result),
		0, 8, 1, 1,
		1, uiAlignFill, 2, uiAlignFill);
	
	return uiControl(vbox);
}


int main(void)
{
	uiInitOptions options;
	const char *err;
	uiTab *tab;

	memset(&options, 0, sizeof (uiInitOptions));
	err = uiInit(&options);
	if (err != NULL) {
		fprintf(stderr, "error initializing libui: %s", err);
		uiFreeInitError(err);
		return 1;
	}

	mainwin = uiNewWindow("Lab_08", 640, 480, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);
	uiOnShouldQuit(onShouldQuit, mainwin);

	tab = uiNewTab();
	uiWindowSetChild(mainwin, uiControl(tab));
	uiWindowSetMargined(mainwin, 1);

	uiTabAppend(tab, "Input", makeBasicControlsPage());
	uiTabSetMargined(tab, 0, 1);

	uiControlShow(uiControl(mainwin));
	uiMain();
	return 0;
}