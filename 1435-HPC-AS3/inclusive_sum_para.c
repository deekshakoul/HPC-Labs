#include <stdio.h>
#include "omp.h"
#include <math.h>
#define SIZE 1024
#define THREADS 4

int main(void){
	long long input[SIZE + 1] /*= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}*/;
	long long depth = log2(SIZE), d, i;
	long long b = 1, b1 = 1;
	
	for(i = 0; i < SIZE; i++)
		input[i] = i+1;
	/*for(i = 0; i < SIZE; i++){
		printf("%lld ", input[i]);
	}*/	
	//printf("\n");

	double time = omp_get_wtime();
	
	/*Up sweep*/
	for(d = 0; d < depth; d++){
		b  <<= 1;
		b1 = b >> 1;
		#pragma omp parallel for num_threads(THREADS) default(shared)
		for(i = 0; i < SIZE; i += b){
			input[i + b - 1] += input[i + b1 - 1];
		}
		/*for(i = 0; i < SIZE; i++){
		printf("%lld ", input[i]);
	}	
	printf("\n");*/
	}
	input[SIZE] = input[SIZE - 1];
	/*Down sweep*/
	input[SIZE - 1] = 0;
	for(d = depth; d > 0; d--){
		b  >>= 1;
		b1 = b << 1;
		#pragma omp parallel for num_threads(THREADS) default(shared)
		for(i = 0; i < SIZE; i += b1){
			long long t = input[i + b - 1];
			input[i + b - 1] = input[i+ b1 - 1];
			input[i + b1 - 1] += t; 
		}
		/*for(i = 1; i < SIZE + 1; i++){
		printf("%lld ", input[i]);
		}	
		printf("\n");*/
	}
	
	printf("TIME : %lf\n", omp_get_wtime() - time);

/*	for(i = 0; i < SIZE; i++){
		printf("%lld ", input[i]);
	}	
	printf("\n");*/
}