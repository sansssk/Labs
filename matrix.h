#ifndef MATRIX_H
#define MATRIX_H

int** create_matrix(int m, int n);
void delete_matrix(int** mat, int m);
void fill_matrix(int** mat, int size);
void print_matrix(int** mat, int size);

#endif