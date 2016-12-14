/*Exclusive Prefix Sum Serial*/
/*Date : 6 Sep, 2015*/
#include <stdio.h>
#include "omp.h"
#define SIZE 1024
int main(int argc, char* argv[]){
	
	long long input[SIZE];
	long long result[SIZE],i;
	long long running_sum = 0;
	for(i = 0; i < SIZE; i++)
		input[i] = i+1;
	double time = omp_get_wtime();
	for( i = 0; i < SIZE; ++i)
	{
		result[i] = running_sum;
		running_sum += input[i];
	}
printf("TIME : %lf\n SIZE = %ld", omp_get_wtime() - time, SIZE);

}