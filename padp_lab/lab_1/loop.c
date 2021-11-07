#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int i,n;
	float a[100], b[100], s;
	n=100;
	for(i=0; i<n;i++)
		a[i] = b[i] = i;
	s=0;
	#pragma omp parallel for reduction(+:s)
	for(i=0; i<n; i++)
		s = s + (a[i]+b[i]);
	printf("s = %f\n", s);
	
}