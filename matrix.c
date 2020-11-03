#include "matrix.h"

#include <stdlib.h>
#include <stdio.h>


void fill_matrix(int** mat, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat[i][j] = i * size + j;
        }
    }
}

void print_matrix(int** mat, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%3d ", mat[i][j]);
        }
        puts("");
    }
    puts("");
}

int** create_matrix(int m, int n)
{
    int** mat = calloc(sizeof(int*), m);
    if (mat == NULL)
    {
        fprintf(stderr, "Can't allocate memory for matrix. Returning NULL.");
        return NULL;
    }

    for (int i = 0; i < m; i++)
    {
        mat[i] = calloc(sizeof(int), n);

        if (mat[i] == NULL)
        {
            fprintf(stderr, "Can't allocate memory for matrix. Returning NULL.");
            for (int j = 0; j < i; j++)
            {
                free(mat[j]);
            }
            free(mat);
            return NULL;
        }
    }
    return mat;
}

void delete_matrix(int** mat, int m)
{
    for (int i = 0; i < m; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

