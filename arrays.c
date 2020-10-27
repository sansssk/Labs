#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
int n;
int i;
printf("Enter elements");
scanf("%d", &n);
int *X = (int*) malloc(n*sizeof(int));
int *Y = (int*) malloc(n*sizeof(int));
for(i=0; i<n; i++)
{
printf("X[%d] ", i);
scanf("%d", &X[i]);
printf("Y[%d] ", i);
scanf("%d", &Y[i]);
}
for(i=0; i<n; i++)
{
printf("X[%d]= %d ", i, X[i]);
printf("Y[%d]= %d ", i, Y[i]);
}

int Z=0;
for(i=0; i<n; i++)
{
Z+=X[i]*Y[n-1-i];
}
printf("Z=%d",Z);
return 0;
}