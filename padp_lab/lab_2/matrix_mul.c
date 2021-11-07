#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	int i=0, t=0;
	for(t=1; t<=8; t=t*2){
	for(i=500; i<=2000; i=i+500){
		int r, j,l, count=0, sum=0,k;
		r= i;
		int** arr1 = (int**)malloc(r * sizeof(int*));
		for(j=0;j<r;j++)
			arr1[j]=(int*)malloc(r*sizeof(int*));

		int** arr2 = (int**)malloc(r * sizeof(int*));
		for(j=0;j<r;j++)
			arr2[j]=(int*)malloc(r*sizeof(int*));

		int** arr3 = (int**)malloc(r * sizeof(int*));
		for(j=0;j<r;j++)
			arr3[j]=(int*)malloc(r*sizeof(int*));

		for(j=0; j<r; j++)
			for(k=0; k<r;k++)
				arr1[j][k] = count++;

		for(j=0; j<r; j++)
			for(k=0; k<r;k++)
				arr2[j][k] = count++;

		double x = omp_get_wtime();
		omp_set_num_threads(t);
		#pragma omp parallel for private(j, k)
		for(j=0;j<r;j++)
			for(k=0;k<r;k++)
				for(l=0;l<r;l++)
					arr3[j][k]+= arr1[j][l]*arr2[l][k];

		double y = omp_get_wtime();
		printf("%d Thread and %d*%d Matrix - %lf\n", t,r,r,y-x);

	}
	}
return 0;
}
