/*Jahnavi Suthar (201301414) and Deeksha Koul (201301435)*/
/**********************************************************
**Calculate value of PI  using serial code*****************
***********************************************************/

#include<stdio.h>
#include"omp.h"

static long num_steps = 10000000;//Divide (4.0 / 1 + x^2) in to num_steps rectangles 

double step;

void main(){
	double time = omp_get_wtime();/*time taken before the start of code*/
	int i;
	double x, pi, sum =0.0;
	step = 1.0 / num_steps;/*function to be integrated is in interval [0,1]*/
	for(i = 0; i < num_steps; i++){
		x = (i + 0.5) * step;
		sum += 4.0 /(1 + x * x);
	}
	pi = sum * step;
	printf("PI = %f", pi);
	printf("Time taken for executing serial code : %lf",omp_get_wtime() - time);
}
