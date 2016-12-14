#include<stdio.h>
#include<omp.h>
#define x 10000
void main()
{	double Time=omp_get_wtime();
	long fib[x];
	long num = x;
	fib[0] = 1;
	fib[1] = 1;
	fib[2] = 2;
	fib[3] = 3;
	fib[4] = 5;
	long k, n;
	k=2;
	n=0;
	omp_set_num_threads(4);
	long count = 0;
	int flag = 0;
	while(count < num)
	{
		k*=2;
	
	 
			#pragma omp parallel private(n)
			{
				int n=omp_get_thread_num();
				while(n<k){
					if((n+k+1)<num)
					{
						fib[n+k+1] = (fib[n+1]*fib[k])+(fib[n]*fib[k-1]);

						n+=4;
					}
					else{
						flag=1;
						break;
					}					
					
				}
			
			}
		if(flag == 1)
			break;	
	}
	printf("%ld %lf\n",num, omp_get_wtime()-Time);
}
