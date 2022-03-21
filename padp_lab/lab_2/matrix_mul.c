#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void main(){
	int n,t;
	for(n=500; n<=2000; n+=500)
		for(t=1; t<16; t*=2){
			int **a,**b,**c;
			a = (int**)malloc(sizeof(int*)*n);
			b = (int**)malloc(sizeof(int*)*n);
			c = (int**)malloc(sizeof(int*)*n);
			int i=0,j,k;
			for(i=0; i<n; i++){
				a[i] = (int*)malloc(sizeof(int)*n);
				b[i] = (int*)malloc(sizeof(int)*n);
				c[i] = (int*)malloc(sizeof(int)*n);
			}
			for(i=0; i<n; i++)
				for(j=0; j<n; j++){
					a[i][j] = i;
					b[i][j] = n-i;
					c[i][j] = 0;
				}
			double t1 = omp_get_wtime();
			omp_set_num_threads(t);
			#pragma omp parallel for private(j,k) shared(a,b,c)
			for(i=0; i<n; i++)
				for(j=0; j<n; j++)
					for(k=0; k<n; k++)
						c[i][j] = a[i][k] * b[k][j];
			double t2 = omp_get_wtime() - t1;
			printf("N: %d Threads: %d Time: %g\n",n,t,t2);
		}
}

