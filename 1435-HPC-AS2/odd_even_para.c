#include<stdio.h>
#include "omp.h"
#define THREADS 4
#define n 1000000
int main(void){
	long long temp, phase, i,a[n];
	
for(i=0;i<n;i++)
            	{	a[n-i-1]=i;
		} 

double time = omp_get_wtime();
		

	for(phase = 0; phase < n; phase++){
		if(phase % 2 == 0){
		#pragma omp parallel num_threads(4) default(shared) private(i, temp)
{  		
                     #pragma omp critical
			for(i = 1; i < n; i = i + 2){
				if(a[i-1] > a[i]){
					temp = a[i-1];
					a[i-1] = a[i];
					a[i] = temp;
				}
			}
		}
}		else{
			#pragma omp parallel num_threads(4) default(shared) private(i, temp)
{			
                       #pragma omp critical
			
			for(i = 1; i < n - 1; i += 2){
				if(a[i] > a[i+1]){
					temp = a[i+1];
					a[i+1] = a[i];
					a[i] = temp;
				}
			}
 		}
	}			
}		printf("Time taken for sorting is: %lf\n", omp_get_wtime() - time);
}
