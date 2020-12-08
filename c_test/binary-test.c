/*using fread() and fwrite() to copy files.*/

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char ** argv)
{
	FILE * filer, * filew;
	int numr,numw;
	char buffer[100];

	if(argc!=3){
		fprintf(stderr,"USAGE: binary-test inputfile outputfile.\n");
		exit(1);
	}
	
	if((filer=fopen(argv[1],"rb"))==NULL){
		fprintf(stderr, "open read file error.\n");
		exit(1);
	}

	if((filew=fopen(argv[2],"wb"))==NULL){
		fprintf(stderr,"open write file error.\n");
		exit(1);
	}
	while(feof(filer)==0){	
	if((numr=fread(buffer,1,100,filer))!=100){
		if(ferror(filer)!=0){
		fprintf(stderr,"read file error.\n");
		exit(1);
		}
		else if(feof(filer)!=0);
	}
	if((numw=fwrite(buffer,1,numr,filew))!=numr){
		fprintf(stderr,"write file error.\n");
		exit(1);
	}
	}	
	
	fclose(filer);
	fclose(filew);
	
	return 0;
}
