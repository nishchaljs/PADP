#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<omp.h>
#include<iostream>
//#include<iostream>
using namespace std;
int strike(bool* comp, long i, long stride, long limit) {
	for (i; i <= limit; i += stride) {
		comp[i] = true;
	}
	return i;
}

int cacheunfriend(int n) {
	bool* comp = (bool*)malloc(sizeof(bool) * (n+1));
	int count = 0;
	memset(comp, false, n+1);
	int m = sqrt(n);
	double t1 = omp_get_wtime();
	for(int i=2; i<=m; i++){
		if (!comp[i]) {
			count++;
			strike(comp, 2 * i, i, n);
		}
	}
	for (int i = m + 1; i <= n; i++) {
		if (!comp[i])
			count++;
	}
	double t2 = omp_get_wtime() - t1;
	printf("N = %d, Time = %g, Count = %d\n", n, t2, count);
	return t2;
}

int cachefriend(int n) {

	
	int count = 0;
	int m = sqrt(n);
	bool* composite = new bool[n + 1];
	memset(composite, 0, n+1);
	int* factor = new int[m];
	int* striker = new int[m];
	int n_factor = 0;
	double t1 = omp_get_wtime();
	for (int i = 2; i <= m; ++i)
		if (!composite[i])
		{
			++count;
			striker[n_factor] = strike(composite, 2 * i, i, m);
			factor[n_factor++] = i;
		}
	// Chops sieve into windows of size ≈ sqrt(n)
	for (int window = m + 1; window <= n; window += m)
	{
		int limit = min(window + m - 1, n);
		for (int k = 0; k <n_factor; ++k)
			// Strike walks window of size sqrt(n) here.
			striker[k] = strike(composite, striker[k], factor[k], limit);
		for (int i = window; i<= limit; ++i)
			if (!composite[i])
				++count;
	}
	double t2 = omp_get_wtime() - t1;
	printf("N = %d, Time = %g, Count = %d\n", n, t2, count);
	return t2;
}

int cacheparallel(int n, int t) {
	int m = sqrt(n);
	int* striker = new int[n];
	int* factor = new int[n];
	bool* comp = new bool[n + 1];
	int count = 0, n_fac=0;
	memset(comp, 0, n + 1);
	double t1 = omp_get_wtime();
	omp_set_num_threads(t);
#pragma omp single
	for (int i = 2; i <= m; i++) {
		if (!comp[i]) {
			++count;
			striker[n_fac] = strike(comp, 2 * i, i, m);
			factor[n_fac++] = i;
		}
	}

#pragma omp parallel for shared(striker, comp, factor) reduction(+:count)
	for (int window = m + 1; window <= n; window += m) {
		int limit = min(window + m - 1, n);
		for (int k = 0; k < n_fac; k++) {
			striker[k] = strike(comp, striker[k], factor[k], limit);
		}

		for (int k = window; k <= limit; k++) {
			if (!comp[k])
				++count;
		}
	}

	double t2 = omp_get_wtime() - t1;
	printf("N = %d, Time = %g, Count = %d, Thread = %d\n", n, t2, count, t);
	return t2;
}

int main() {
	int t, n;
	for (n = 1000000; n <= 100000000; n *= 10) {
		cacheunfriend(n);
		cachefriend(n);
		cacheparallel(n, 8);
	}
	return 0;
}