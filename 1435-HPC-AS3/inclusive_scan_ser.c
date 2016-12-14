#include <stdio.h>
#include "omp.h"
#define SIZE 8

int main(void){
	
	int input[SIZE] = {3, 1, 7, 0, 4, 1, 6, 3};
	int result[SIZE];
	int running_sum = 0;
	double time = omp_get_wtime();
	for(int i = 0; i < 8; ++i)
	{
		running_sum += input[i];
		result[i] = running_sum;
		
	}
	printf("TIME : %lf\n SIZE = %ld", omp_get_wtime() - time, SIZE);
}