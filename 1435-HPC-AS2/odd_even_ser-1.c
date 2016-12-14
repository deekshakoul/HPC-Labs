#include<stdio.h>
#include<omp.h>
void swap(long long *a, long long *b){
		long long temp = *a;
		*a = *b;
		*b = temp;
}

int main(void){  long long n=1000;
		double time = omp_get_wtime();
		long long phase,i,a[n];
	for(i=0;i<n;i++)
            {	a[n-i-1]=i;
		} 

		
		for(phase = 0; phase < n; phase++){
			if(phase % 2 == 0)
				for(i = 1; i < n; i += 2){
					if(a[i-1] > a[i]) swap(&a[i-1], &a[i]);
				}
			else
				for(i = 1; i < n - 1; i=i+2)
					if(a[i] > a[i+1]) 
						swap(&a[i], &a[i+1]);
		}
		printf("Time taken for sorting for n=%lld is: %lf\n",n, omp_get_wtime() - time);
}
