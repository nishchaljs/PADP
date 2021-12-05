#include<stdio.h>
#include<gd.h>
#include<error.h>
#include<omp.h>
#include<stdlib.h>
int main(int argc, char** argv){
	if(argc!=3){
		error(1,0,"Invalid args. Try ./a.out inp.png out.png");
		return 0;
	}
	else{
		FILE *inp, *op;
		if((inp = fopen(argv[1],"r"))==NULL){
			error(1,0,"INP FILE CANNOT BE OPENED");
			return 0;
		}
		else{int t;
		     gdImagePtr img;
		     img = gdImageCreateFromPng(inp);
			for(t=1; t<16; t*=2){
			int w = gdImageSX(img);
			int h = gdImageSY(img);
			int i=0,j;
			double t1 = omp_get_wtime();
			omp_set_num_threads(t);
			#pragma omp parallel for private(i,j) shared(img)
			for(i=0; i<w; i++)
				for(j=0; j<h; j++)
				{
					int tid = omp_get_thread_num();
					int color = gdImageGetPixel(img,i,j);
					int red = gdImageRed(img,color);
					int green = gdImageGreen(img, color);
					int blue = gdImageBlue(img, color);
					int temp = (red+green+blue)/3;
					red=green=blue=temp;
					if(tid==0){
						color = gdImageColorAllocate(img,red,green,blue);
						gdImageSetPixel(img,i,j,color);
						}
					if(tid==1){
						color = gdImageColorAllocate(img,red,green,blue);
						gdImageSetPixel(img,i,j,color);
						}
					if(tid==2){
						color = gdImageColorAllocate(img,red,green,blue);
						gdImageSetPixel(img,i,j,color);
						}
					if(tid==3){
						color = gdImageColorAllocate(img,red,green,blue);
						gdImageSetPixel(img,i,j,color);
						}
					
				}
			double t2 = omp_get_wtime() -t1;
			printf("The time taken is %g\n", t2);
			}
			op = fopen(argv[2],"w");
			gdImagePng(img,op);
			gdImageDestroy(img);

		
	}
	}
	return 0;
}