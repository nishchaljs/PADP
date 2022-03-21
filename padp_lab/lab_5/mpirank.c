#include<stdio.h>
#include<string.h>
#include<mpi.h>
void main(int argc, char** argv){
	int rank,size;
	char temp[40];
	int n=32;
	char msg[3][40]={"Hi","This is","Nishchal"};
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0){
		int i =0;
		for(i=1; i<size; i++){
			MPI_Status status;
			MPI_Recv(&temp,n,MPI_CHAR,i,0,MPI_COMM_WORLD,&status);
			printf("%s from rank %d to rank %d\n",temp,i,rank);
		}
	}
	else{
		strcpy(temp,msg[rank-1]);
		MPI_Send(&temp,n,MPI_CHAR,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
