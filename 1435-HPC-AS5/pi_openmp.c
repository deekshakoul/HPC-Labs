/*Jahnavi Suthar (201301414) and Deeksha Koul (201301435)*/
/**********************************************************
**Calculate value of PI  using parallel code*****************
***********************************************************/

#include<stdio.h>
#include "omp.h"
static long num_steps = 10000000;
double step;
#define n 4  /*can change the number of cores*/

//#pragma omp critical
long sum =0.0; /*global variable*/

void main(){
	double time = omp_get_wtime();
	double x, pi;
	step = 1.0 / num_steps;
	int d =  num_steps / n;
	#pragma omp parallel private(x)
	{
	int i=0;
	double sum1 = 0;
	double f = step*d * omp_get_thread_num();
	for(i = 0; i < num_steps /n; i++){
		x =  f +( i + 0.5) * step;
		sum1 += 4.0 /(1 + x * x); /*local variable for each thread*/

   		
	}
		sum += sum1 ;

	}
	pi = sum * step;
	printf("PI = %f\n", pi);
	printf("Time taken for executing parallel code : %lf\n",omp_get_wtime() - time);
	
}
