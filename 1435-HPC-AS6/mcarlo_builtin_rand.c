#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
//#define N 100000000  /* As lareg as possible for increased accuracy */

double random_function(void);

int main(int argc,char** argv)
{
   int th_id,n,i = 0;
    double X, Y;long N;
   double count_inside_temp = 0.0, count_inside = 0.0;
  // unsigned int th_id = omp_get_thread_num();
	n=atoi(argv[1]);
	N = atol(argv[2]);
	double start=omp_get_wtime();
   #pragma omp parallel num_threads(n) private(i,th_id, X, Y)  \
         reduction(+:count_inside_temp)
      {
	  th_id = omp_get_thread_num();
      srand(th_id);
      #pragma omp for schedule(static)
      for (i = 0; i < N; i++) {
         X = 2.0 * (double) rand() / (double) RAND_MAX - 1.0;
         Y = 2.0 * (double) rand() / (double) RAND_MAX - 1.0;
         if ((X * X) + (Y * Y) <= 1.0) {
        count_inside_temp += 1.0;
     }
  }
     
   }
	//	printf("core : %d \n",n);
	  printf("%lf\n",omp_get_wtime()-start);
   
 //  printf("Approximation to PI for number of cores is %d is = %.10lf, Time is %lf\n", n,(count_inside_temp * 4.0)/ N,omp_get_wtime()-start);
   return 0;
}
/*
double random_function(void)
{
   return ((double) rand() / (double) RAND_MAX);
}
*/
