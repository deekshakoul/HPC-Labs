#include<math.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#define THREADS 4
#define num 10

int main(int argc , char** argv){
	long SIZE = atol(argv[1]);
	long long  array[SIZE];
	long long  bit[SIZE + 1] ;
	long long output[SIZE];
	long long t;
for(t=0;t<SIZE+1;t++)
	{	bit[t]=0;
	}
	srand(time(NULL));
	for(t = 0; t < SIZE; t++){
		array[t] = rand() % 100;
	}

	double time = omp_get_wtime();
	#pragma omp parallel num_threads(THREADS) default(shared)
	for(t = 0; t < SIZE; t++){
		if(array[t] > num){
			bit[t] = 1; 
		}
	}
	
	long long depth = log2(SIZE), d, i;
	long long b = 1, b1 = 1;
	
	for(d = 0; d < depth; d++){
		b  <<= 1;
		b1 = b >> 1;
		#pragma omp parallel for num_threads(THREADS) default(shared)
		for(i = 0; i < SIZE; i += b){
			bit[i + b - 1] += bit[i + b1 - 1];
		}
	}
		bit[SIZE] = bit[SIZE - 1];
	
	bit[SIZE - 1] = 0;
	for(d = depth; d > 0; d--){
		b  >>= 1;
		b1 = b << 1;
		#pragma omp parallel for num_threads(THREADS) default(shared)
		for(i = 0; i < SIZE; i += b1){
			long long t1 = bit[i + b - 1];
			bit[i + b - 1] = bit[i+ b1 - 1];
			bit[i + b1 - 1] += t1; 
		}
	}
int c=0;
if(bit[1] == 1) output[0] = array[0];
	
	#pragma omp parallel for num_threads(THREADS) default(shared)
	for(i = 1; i < SIZE + 1; i++){
		if(bit[i] > bit[i - 1]){
			output[bit[i] - 1] =  array[i - 1];
                           c++;
		}
	}

	printf("\nTIME : %lf\n", omp_get_wtime() - time);
for(t=0;t<c;t++)
	{ printf("\n%lld\t",output[t]);}
printf("\ncount is : %d\n ", c);


}
