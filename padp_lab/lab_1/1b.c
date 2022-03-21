#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
void main(int argc, char** argv){
	int n=100000, seed = 35792468;
	MPI_Init(&argc,&argv);
	for(n=100000; n<=100000000; n*=10){
		int rank, count=0; double t1,t2;
		int red_count=0, red_iter=0, iter=n;
		MPI_Comm_rank(MPI_COMM_WORLD,&rank);
		if(rank==0){
			t1 = MPI_Wtime();
		}
		else{
			int i=0;
			for(i=0; i<iter; i++){
				double x = (double)rand_r(&seed)/RAND_MAX;
				double y = (double)rand_r(&seed)/RAND_MAX;
				double z = x*x + y*y;
				if(z<=1)
					count++;
			}
		}
		MPI_Reduce(&iter,&red_iter,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
		red_iter = red_iter - iter;
		MPI_Reduce(&count,&red_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
		if(rank==0){
			t2 = MPI_Wtime() - t1;
			double pi = (double)red_count/red_iter*4;
			printf("Iter:%d, Pi: %g, Time: %g\n",n,pi,t2);
		}
	}
	MPI_Finalize();
}

