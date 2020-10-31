// Заданы массивы X={ X[0], ..., X[n-1]} и Y={ Y[0], ..., Y[n-1]}.
// Вычислить:
// Z= X[0] * Y[n-1] + X[1] * Y[n-2] + ... + X[n-1] * y[0].

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    printf("Enter arrays len (positive integer): \n");
    int len;
    if (!scanf("%d", &len)) //ф-ия возвр. кол-во корректно считанных значений
    {
        fprintf(stderr, "Error format length.\n");
        return 1;
    }

    int *X = (int*) calloc(len,sizeof(int));
    if (X == NULL)
    {
        fprintf(stderr, "Error memory allocate.\n");
        return 1;
    }

    int *Y = (int*) calloc(len, sizeof(int));
    if (Y == NULL)
    {
        fprintf(stderr, "Error memory allocate.\n");
        return 1;
    }

    puts("Enter  arrays elements :");
    for (int i = 0; i < len; i++)
    {
        printf ("X[%d] = ", i);
        if (!scanf("%d", &X[i]))
        {
            fprintf(stderr, "Error element format.\n");
            return 1;
        }

        printf ("Y[%d] = ", i);
        if (!scanf("%d", &Y[i]))
        {
            fprintf(stderr, "Error element format.\n");
            return 1;
        }
        puts("");
    }

    int Z = 0;
    for (int i = 0; i < len; i++)
    {
        Z += X[i] * Y[len - 1 - i];
    }

    printf("Formula Z = X[0]*Y[n]+...+X[n]*Y[0]\nZ = %d\nFor arrays:\n", Z);
    for(int i = 0; i < len; i++)
    {
        printf("X[%d]= %d \n", i, X[i]);
        printf("Y[%d]= %d \n", i, Y[i]);
    }

    free(X);
    free(Y);
    return 0;
}