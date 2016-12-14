#include<stdio.h>
#include "omp.h"

void main(){
  long   N=100,j,temp,first,i;

  // long   a[N];

      /*  for (i=0;i<N;i++)
         {  //backward sorted array     
          a[N-i-1]=i;
        }*/
while(N<100005){
       long   a[N];
       for (i=0;i<N;i++)
         {  //backward sorted array     
          a[N-i-1]=i;
       }
double time = omp_get_wtime();
for ( i = 0; i < N; i++ )
{
first = i % 2;  // 0 if i is 0, 2, 4, ...
                   // 1 if i is 1, 3, 5, ...
                     #pragma omp parallel for num_threads(2) private(temp)\
                              default(shared)
                         for(j = first; j < N-1; j += 2 )
                                {
                                        if( a[j] > a[j + 1])
                                         {
                                             temp = a[j];
                                             a[j] = a[j+1];
                                            a[j+1] = temp;
                                                                                                         }

                                }

                                }




                 printf("\nTIME IS %lf  and  n is  %ld \n",omp_get_wtime()-time,N);
N=N*10;
}                                                                                                                                                                           }

