#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int create_matrix(int **matrix, int n, int m)
{
matrix = (int**)malloc(n * sizeof(int*));
for (int i = 0; i<m; i++)
{
matrix[i] = (int*)malloc(m * sizeof(int));
}
return **matrix;
}

int scan_matrix(int **matrix, int n, int m)
{
int i, j;
for (i = 0; i<n; i++)
for(j = 0; j<m; j++)
{
scanf("%d", &matrix[i][j]);
}
return **matrix;
}

void print_matrix(int **matrix, int n, int m)
{
int i, j;
for (i = 0; i<n; i++)
{
for(j = 0; j<m; j++)
{
printf("%d ", matrix[i][j]);
}
printf("\n");
}
}

int main()
{
int **matrix, n, m;

printf("Введите кол-во строк и столбцов ");
scanf("%d %d", &n, &m);

create_matrix(matrix, n, m);

scan_matrix(matrix, n, m);

print_matrix(matrix, n, m);

return 0;
}