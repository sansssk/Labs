#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_columns(int** mat, int size) {
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size; j++) {
            swap(&mat[j][i], &mat[j][size - 1 - i]);
        }
    }
}

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

int main() {
    printf("Enter matrix size: ");

    int size = 0;
    scanf("%d", &size);

    int** mat = calloc(sizeof(int), size); 
    for (int i = 0; i < size; i++) {
        mat[i] = calloc(sizeof(int), size); 
    }
    
    fill_matrix(mat, size);
    print_matrix(mat,size);
    swap_columns(mat, size);
    print_matrix(mat,size);

    return 0;
}