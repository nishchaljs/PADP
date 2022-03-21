#include<stdio.h>
#include<omp.h>
#include<gd.h>
#include<stdlib.h>
void main(int argc, char** argv){
	if(argc<3){
		printf("Enter ./a.out inp.png op.png\n");
		return;
	}
	FILE* fp;
        fp = fopen(argv[1], "r");
	if(fp==NULL){
		printf("FILE NO SUPPORTED\n");
		return;
	}
	gdImagePtr image;
	image = gdImageCreateFromPng(fp);
	int w = gdImageSX(image);
	int h = gdImageSY(image);
	int i,j;
	//printf("HEYYY\n");
	omp_set_num_threads(3);
	double t1 = omp_get_wtime();
#pragma omp parallel for private(j) shared(image) schedule(dynamic,10) //static, dynamic, guided
	for(i=0; i<w; i++)
		for(j=0; j<h; j++){
			int tid = omp_get_thread_num();
			int color = gdImageGetPixel(image,i,j);
			int red = gdImageRed(image,color);
			int green = gdImageGreen(image,color);
			int blue = gdImageBlue(image,color);
			int temp = (red+green+blue)/3;
			red = green = blue = temp;
			if(tid==0){
				color = gdImageColorAllocate(image,red,0,0);
			        gdImageSetPixel(image,i,j,color);
			}
			if(tid==1){
				color = gdImageColorAllocate(image,0,green,0);
			        gdImageSetPixel(image,i,j,color);
			}
			if(tid==2){
				color = gdImageColorAllocate(image,0,0,blue);
			        gdImageSetPixel(image,i,j,color);
			}
		}
	double t2 = omp_get_wtime() - t1;
	printf("Time:%g\n",t2);
	FILE* fp1 = fopen(argv[2], "w");
	gdImagePng(image,fp1);
	//fclose(fp1);
	gdImageDestroy(image);
	//fclose(fp);
}
