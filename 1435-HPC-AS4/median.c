#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include<omp.h>


int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

// half width = 3
int getMedian(char** arr, int h, int w, int x, int y) {
	int nBors[8] = {0};
	if(x > 0 && y > 0) {
		nBors[0] = arr[x-1][y-1];
		if(y < h-1)
		nBors[2] = arr[x-1][y+1];
	}
	if(x > 0)
		nBors[1] = arr[x-1][y];
	if(y > 0)
		nBors[3] = arr[x][y-1];
	if(y < h-1)
		nBors[4] = arr[x][y+1];
	if(x > 0 && x < h-1 && y > 0) {
		nBors[5] = arr[x+1][y-1];
		nBors[6] = arr[x+1][y];
		if(y < h-1)
		nBors[7] = arr[x+1][y+1];
	}
	qsort(nBors, 8, sizeof(int), cmpfunc);
	return nBors[4];
}

void median(char* input,char* output,int threads) {
	FILE* f = fopen(input,"rb");
	FILE* fp = fopen(output,"wb");
	int i = 0, size = 0, h, w;
	if(f == NULL) {
		printf("could not open file\n");
		return;
	} else if(fp == NULL) {
		printf("could not write to file\n");
		return;
	} else {
		fseek(f,18,SEEK_SET);
		fread(&h,sizeof(int),1,f);
		fseek(f,22,SEEK_SET);
		fread(&w,sizeof(int),1,f);
		fseek(f,34,SEEK_SET);
		fread(&size,sizeof(int),1,f);
		fseek(f,0,SEEK_SET);
		char c;
		while(i < 54) {
			fread(&c, sizeof(char),1,f);
			fwrite(&c,sizeof(char),1,fp);
			i++;
		}
		
			int j,k;
			char **arr = (char **)malloc(h * sizeof(char *));
			for (i=0; i<h; i++)
				 arr[i] = (char *)malloc(w * sizeof(char));
			for(j=0;j<h;j++) {
				for(k=0;k<w;k++) {
					fread(&c, sizeof(char),1,f);
					arr[j][k] = c;
					int temp = atoi(&arr[j][k]);
					//i++;	
				}
			}
			double start=omp_get_wtime();
			int index, xp, yp, tx = w/2, ty = h/2;

			#pragma omp omp_num_threads(threads) parallel for private(yp,xp,c) shared(h,w,fp,arr) schedule(dynamic,tx)
			for(yp=0;yp<h;yp++) {				
				for(xp=0;xp<w;xp++) {
					c = (char)getMedian(arr,h,w,yp,xp);					
					fwrite(&c,sizeof(char),1,fp);	
 				}
			}

			double end=omp_get_wtime();
			printf("TIME FOR MEDIAN FILTER IS%lf \n",(end-start));
			
		
		fclose(f);
		fclose(fp);
	}
	return;	
}

int main(int *argc, char* argv[]) {
	//twist(argv[2],argv[3],atoi(argv[1]));
	
	median(argv[2],argv[3],atoi(argv[1]));
	
	
	return 0;
}