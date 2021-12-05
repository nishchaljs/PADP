#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<string.h>
#include<error.h>
int isalpha(int c){
	return(c>=65 && c<=90 || c>=97 && c<=122);
}
int isequal(char* temp, char* key, int caseflag){
	if(caseflag==1){
		int temp_len = strlen(temp), key_len = strlen(key);
		if(temp_len!=key_len)
			return -1;
		int i;
		for(i=0; i<temp_len; i++){
			int x = temp[i];
			if(x >= 97 && x <= 122)
				temp[i]-=32;
		}
		for(i=0; i<key_len; i++){
			int x = key[i];
			if(x >= 97 && x <= 122)
				key[i]-=32;
		}
		return strcmp(temp,key);
	}
	else{
		return strcmp(temp,key);
	}
}
void read_word(char* temp, FILE* fp){
	int i=0;
	char ch;
	while((ch = fgetc(fp))!=EOF && isalpha(ch)==0);
	while(ch!=EOF && isalpha(ch)!=0){
		temp[i++] = ch;
		ch = fgetc(fp);
	}
	temp[i] = '\0';
}
int search_word(char* key, FILE* fp){
	int count = 0;
	char temp[40];
	while(feof(fp)==0){
		read_word(temp,fp);
		if(isequal(temp,key,1)==0)
			count+=1;
	}
	return count;
}
int main(){

	char keys[20][10]={"The","around","graphics","from","by","be","any","which","various","mount"};
	int i;
	#pragma omp parallel for private(i) shared(keys)
	for(i=0; i<10; i++){
		FILE *fp;
		fp=fopen("words.txt","r");
		int count = search_word(keys[i],fp);
		fclose(fp);
		printf("%s - %d\n", keys[i], count);
	}
	return 0;
}