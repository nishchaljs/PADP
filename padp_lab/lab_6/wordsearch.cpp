#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>
#include<ctype.h>
int is_equal(char* temp, char* w){
	int tl = strlen(temp), wl = strlen(w);
	if(tl!=wl)
		return 1;
	int i;
	for(i=0; i<tl; i++)
		if(temp[i]>=97)
			temp[i]-=32;
	for(i=0; i<wl; i++)
		if(w[i]>=97)
			w[i]-=32;
	return strcmp(w,temp);
}
void get_word(char* temp, FILE* fp){
	char ch;
	int i=0;
	while((ch=fgetc(fp))!=EOF && !isalpha(ch));
	while(ch!=EOF && isalpha(ch)){
		temp[i++]=ch;
		ch = fgetc(fp);
	}
	temp[i]='\0';
}
int search(FILE* fp, char* w){
	char temp[40];
	int count=0;
	while(feof(fp)==0){
		get_word(temp,fp);
		if(is_equal(temp,w)==0)
			count++;
	}
	return count;

}
void main(){
	int t;
	char w[10][40]={"Hi", "name", "nish", "sup", "you"};
	int i=0;
	for(t=1; t<16; t*=2){
		double t1 = omp_get_wtime();
		omp_set_num_threads(t);
		#pragma omp parallel for shared(w)
		for(i=0; i<5; i++){
			FILE* fp = fopen("words.txt","r");
			if(fp==NULL)
				exit(0);
			int count = search(fp,w[i]);
			printf("%s - %d\n",w[i],count);
			fclose(fp);
		}
		double t2 = omp_get_wtime() - t1;
		printf("Threads: %d  Time: %g\n", t,t2);
	}
}
