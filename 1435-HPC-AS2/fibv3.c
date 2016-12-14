#include <stdio.h>
#include <omp.h>
double fib(double n)
{  

  int i, j;
  if (n<2)
    return n;
  else
    {
       #pragma omp task shared(i) firstprivate(n)
       i=fib(n-1);

       #pragma omp task shared(j) firstprivate(n)
       j=fib(n-2);

       #pragma omp taskwait
       return i+j;
    }
}

int main()
{   double time=omp_get_wtime();
 double n = 35;

  omp_set_dynamic(0);
  omp_set_num_threads(4);

  #pragma omp parallel shared(n)
  {
    #pragma omp single
    printf ("fib(%lf) = %lf\n", n, fib(n));
  }
printf("TIME TAKEN IS:%lf",omp_get_wtime()-time);
}
