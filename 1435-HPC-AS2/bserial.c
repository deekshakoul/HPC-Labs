#include<stdio.h>
#include "omp.h"

void main(){
   long n=1000000;
 
      double time = omp_get_wtime();
      long  a[n];
      long list_length, i;
 
	for (i=0;i<n;i++)
	 {  	
	  a[n-i-1]=i;
	}

        for(list_length = n; list_length >= 2; list_length--){
                for(i = 0; i < list_length-1; i++){
                        if(a[i] > a[i+1])
                            {
                            int temp = a[i];
                            a[i] = a[i+1];
			    a[i+1] = temp;   
                                                                                                                                                                       
						}
				}
		}

printf("\nTIME IS %lf  and  n is  %ld\n",omp_get_wtime()-time,n);

}
				
