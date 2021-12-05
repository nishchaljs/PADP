#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char** argv){
	char msg[3][20]={"HELLO","NISHCHAL","HERE"};
	char temp[40];
	int BUF_SIZE=32;
	int root=0,tag=0,rank=0,size=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0){
		int i=0;
		for(i=1; i<size; i++){
		MPI_Status status;
		MPI_Recv(&temp,BUF_SIZE,MPI_CHAR,i,tag,MPI_COMM_WORLD,&status);
		printf("Msg=%s recv from %d rank to %d rank\n",temp,i,rank);
	}
	}
	else{		strcpy(temp,msg[rank-1]);
			MPI_Send(&temp,BUF_SIZE,MPI_CHAR,0,tag, MPI_COMM_WORLD);
		}
	MPI_Finalize();
}
