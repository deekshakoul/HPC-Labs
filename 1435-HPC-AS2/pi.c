#include<stdio.h>
#include<math.h>
#include"omp.h"
void main(){
	double time = omp_get_wtime();
double pi, sum=0.0,factor = 1.0;
long i=0;long n=10000;
for( i=0;i<n;i++)
{
sum = sum + (factor / (2 * i + 1) );
//factor = -factor;
if(i % 2 == 0)
   factor = -1.0 ;
else 
   factor = 1.0 ;
 }
pi = 4.0 * sum ;
printf("Pi value through serial code is %lf\n",pi);
printf("%lf\n",omp_get_wtime() - time);
}
