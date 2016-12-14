#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <time.h>

int main(int argc , char** argv){
	long SIZE = atol(argv[1]);
	int array[SIZE];
	int output[SIZE];
	int i, count = 0;
	srand(time(NULL));
	for(i = 0; i < SIZE; i++){
		array[i] = rand(); 
	}
	double time = omp_get_wtime();
	
	for(i = 0; i < SIZE; i++){
		if(array[i] > 10){
			output[count++] = array[i]; 
		}
	}
	printf("TIME : %lf", omp_get_wtime() - time);
}