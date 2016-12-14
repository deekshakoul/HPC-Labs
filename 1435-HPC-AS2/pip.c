#include<stdio.h>
#include<math.h>
#include"omp.h"
void main(){
	double time = omp_get_wtime();
	double sum = 0.0, pi;
	long i, n = 10000;
	double factor = 1.0;
	#pragma omp parallel for num_threads(4)\
          default(none) reduction(+:sum) private(i, factor)\
           shared(n)
		for(i = 0;i < n;i++)
		{
			//factor = -factor;
			if(i % 2 == 0)
   				factor = 1.0 ;
			else 
   				factor = -1.0 ;
                     
			sum = sum + (factor / (2 * i + 1) );
		}


	pi = 4.0 * sum ;
	printf("Pi value through parallel code is %lf\n",pi);
	printf("%lf\n",omp_get_wtime() - time);
}
