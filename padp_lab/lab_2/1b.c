#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define seed 35791246
void main(int argc, char** argv) {

	MPI_Init(&argc, &argv);
	int iter = 0;
	for (iter = 1000000; iter <= 100000000; iter *= 10) {
		srand(seed);
		int rank, count=0, red_iter, red_count;
		double t1;
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		if (rank == 0) {
			t1 = MPI_Wtime();
		}
		if(rank>0){
			int i;
			for (i = 0; i < iter; i++) {
				double x = (double)rand() / RAND_MAX;
				double y = (double)rand() / RAND_MAX;
				double z = x * x + y * y;
				if (z <= 1) count++;
			}
	}
		MPI_Reduce(&iter, &red_iter, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&count, &red_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		red_iter = red_iter - iter;
		if (rank == 0) {
			double t2 = MPI_Wtime() - t1;
			double pi = (double)red_count / red_iter * 4;
			printf("%g for %d iter in %g time\n", pi, iter, t2);
		}
		
		

}
MPI_Finalize();
}
