#include <math.h>
#include <stdio.h>

int main()
{
float a, b, h;

scanf ("%f %f %f", &a, &b, &h);
if ( h == 0 )
{
printf ("Ne rabotaet\n");
return 0;
}
for (; a<b; a+=h)
{
printf("%f", ((exp(a)+exp(-a)))/2);
}


return 0;
}