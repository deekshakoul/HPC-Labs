#include<stdio.h>
#include"omp.h"
void main(){   long n =100;
       
	double time=omp_get_wtime();
	
	long  long i;
	long long fib[n],k;
	fib[0]=1;
	fib[1]=1;
	for(i = 2 ; i < n ; i++){
	 	fib[i] = fib[i-1] + fib[i-2]; 
	//	printf("%ld\n", fib[i]);
	}

	        printf("\n");      
printf(" time is : %lf, number of input is: %ld",omp_get_wtime()-time,n);

}

