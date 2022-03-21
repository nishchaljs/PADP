#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void main(){
	long n; int t, seed = 35792468;
	for(n=10000; n<100000000; n*=10)
		for(t=1; t<16; t*=2){
			double pi; long i; int count = 0;
			double t1 = omp_get_wtime();
			omp_set_num_threads(t);
			#pragma omp parallel for reduction(+:count)
			for(i=0; i<n; i++){
				double x = (double)rand_r(&seed)/RAND_MAX;
				double y = (double)rand_r(&seed)/RAND_MAX;
				double z = x*x + y*y;
				if(z<=1)
					count++;
			}
			pi = (double)count/n*4;
			double t2 = omp_get_wtime()-t1;
			printf("Iter: %ld, Threads: %d, Pi: %g, Time: %g\n",n,t,pi,t2);

		}
}
