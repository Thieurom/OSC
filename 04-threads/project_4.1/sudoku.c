/*
 * Programming Project 4.1
 * =========================
 * Sudoku Solution Validator
 */


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREADS 27

typedef struct {
    int row;
    int column;
} cell;

cell *new_cell(int row, int column);
void *validate_row(void *cell_param);
void *validate_column(void *cell_param);
void *validate_subgrid(void *cell_param);


/****************************************************************************/


int sudoku[9][9] = {
	{6, 2, 4, 5, 3, 9, 1, 8, 7},
	{5, 1, 9, 7, 2, 8, 6, 3, 4},
	{8, 3, 7, 6, 1, 4, 2, 9, 5},
	{1, 4, 3, 8, 6, 5, 7, 2, 9},
	{9, 5, 8, 2, 4, 7, 3, 6, 1},
	{7, 6, 2, 3, 9, 1, 4, 5, 8},
	{3, 7, 1, 9, 5, 6, 8, 4, 2},
	{4, 9, 6, 1, 8, 2, 5, 7, 3},
	{2, 8, 5, 4, 7, 3, 9, 1, 6}
};

int validity[N_THREADS];

int main()
{
    pthread_t validators[N_THREADS];
    pthread_attr_t attr;
    cell *rowp, *colp, *gridp;
    int i, j;

    pthread_attr_init(&attr);

    /* create threads for row validators */
    for (i = 0; i < 9; i++) {
        rowp = new_cell(i, 0);
        pthread_create(&validators[i], &attr, validate_row, rowp);
    }

    /* create threads for column validators */
    for (i = 0; i < 9; i++) {
        colp = new_cell(0, i);
        pthread_create(&validators[i+9], &attr, validate_column, colp);
    }

    /* create threads for subgrid validators */
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            gridp = new_cell(3*i, 3*j);
            pthread_create(&validators[i+j+18], &attr, validate_subgrid, gridp);
        }
    }

    /* wait for all validators return */
    for (i = 0; i < N_THREADS; i++)
        pthread_join(validators[i], NULL);

    /* report validation result */
    for (i = 0; i < N_THREADS; i++)
        if (validity[i] == 0) {
            printf("Sudoku solution is invalid.\n");
            exit(EXIT_SUCCESS);
        }

    printf("Sudoku solution is valid.\n");

    return EXIT_SUCCESS;
}


cell *new_cell(int row, int column)
{
    cell *new_cell;

    if ((new_cell = (cell *) malloc(sizeof(cell))) == NULL) {
        fprintf(stderr, "Fail allocated memory.\n");
        exit(EXIT_FAILURE);
    }

    new_cell->row = row;
    new_cell->column = column;

    return new_cell;
}

void *validate_row(void *cell_param)
{
    cell *param = (cell *) cell_param;
    int row = param->row;
    int valid_array[9] = { 0 };
    int i, n;

    for (i = 0; i < 9; i++) {
        n = sudoku[row][i];
        if (n < 0 || n > 9 || valid_array[n-1] == 1)
            pthread_exit(0);
        else
            valid_array[n-1] = 1;
    }

    validity[row] = 1;
    pthread_exit(0);
}

void *validate_column(void *cell_param)
{
    cell *param = (cell *) cell_param;
    int col = param->column;
    int valid_array[9] = { 0 };
    int i, n;

    for (i = 0; i < 9; i++) {
        n = sudoku[i][col];
        if (n < 0 || n > 9 || valid_array[n-1] == 1)
            pthread_exit(0);
        else
            valid_array[n-1] = 1;
    }

    validity[col+9] = 1;
    pthread_exit(0);
}

void *validate_subgrid(void *cell_param)
{
    cell *param = (cell *) cell_param;
    int row = param->row;
    int col = param->column;
    int valid_array[9] = { 0 };
    int i, j, n;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            n = sudoku[i+row][j+col];
            if (n < 0 || n > 9 || valid_array[n-1] == 1)
                pthread_exit(0);
            else
                valid_array[n-1] = 1;
        }
    }

    validity[row+col/3+18] = 1;
    pthread_exit(0);
}
