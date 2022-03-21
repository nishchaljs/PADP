#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
int min(int a, int b)
{
	return a<b?a:b;
}
int strike(int* comp,int start, int stride, int limit){
	for(start; start<=limit; start+=stride)
		comp[start] = 1;
	return start;
}
void unfriend(int n){
	int m = sqrt(n);
	int i=0, count=0;
	int* comp = (int*)malloc(sizeof(int)*(n+1));
	for(i=0; i<n+1; i++)
		comp[i] = 0;
	double t1 = omp_get_wtime();
	for(i=2; i<=m; i++)
		if(!comp[i]){
			count++;
			strike(comp,2*i,i,n);
		}
	for(i=m+1; i<=n; i++)
		if(!comp[i])
			count++;
	double t2 = omp_get_wtime() - t1;
	printf("Type: Unfriendly  N: %d  Prime: %d  Time: %g\n",n,count,t2);
}

void friend(int n){
       int m = sqrt(n);
       int i=0, count=0, nfac=0;
       int striker[m], factor[m];
       int* comp = (int*)malloc(sizeof(int)*(n+1));
       for(i=0; i<n; i++)
	       comp[i]=0;
       double t1 = omp_get_wtime();
       for(i=2; i<=m; i++)
	       if(!comp[i]){
		       count++;
		       striker[nfac] = strike(comp,2*i,i,m);
		       factor[nfac++] = i;
	       }

       for(i=m+1; i<=n; i+=m){
	       int lim = min(i+m-1,n);
	       int j;
	       for(j=0; j<nfac; j++)
		       striker[j] = strike(comp,striker[j],factor[j],lim);
	       for(j=i; j<=lim; j++)
		       if(!comp[j])
			       count++;
       }

       double t2 = omp_get_wtime() - t1;
       printf("Type: Friendly  N: %d  Prime: %d  Time: %g\n",n,count,t2);  
}       

void parallel(int n){
       int m = sqrt(n);
       int i=0, count=0, nfac=0;
       int striker[m], factor[m];
       int* comp = (int*)malloc(sizeof(int)*(n+1));
       for(i=0; i<n; i++)
               comp[i]=0;
       double t1 = omp_get_wtime();
       omp_set_num_threads(8);
	#pragma omp single
       for(i=2; i<=m; i++)
               if(!comp[i]){
                       count++;
                       striker[nfac] = strike(comp,2*i,i,m);
                       factor[nfac++] = i;
               }
	#pragma omp parallel shared(striker, factor, comp) reduction(+:count) 
       for(i=m+1; i<=n; i+=m){
               int lim = min(i+m-1,n);
               int j;
               for(j=0; j<nfac; j++)
                       striker[j] = strike(comp,striker[j],factor[j],lim);
               for(j=i; j<=lim; j++)
                       if(!comp[j])
                               count++;
       }

       double t2 = omp_get_wtime() - t1;
       printf("Type: Parallel  N: %d  Prime: %d  Time: %g\n",n,count,t2);
}

void main(){
	int n=0;
	for(n=1000000; n<=100000000; n*=10){
		unfriend(n);
		friend(n);
		parallel(n);
		printf("\n");
	}
}
