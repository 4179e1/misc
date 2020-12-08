#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	void filecomp(FILE *, FILE*);

	char *prog = argv[0];

	if(argc != 3){
		fprintf(stdout, "%s: incorrect number of arguments\n", prog);
		exit(1);
	} else {
		if ((fp1 = fopen(*++argv, "r")) == NULL) {
			fprintf(stdout, "%s: can't open %s\n", prog, *argv);
			exit(2);
		} else if ((fp2 = fopen(*++argv, "r")) == NULL ) {
			fprintf(stdout, "%s: can't open %s\n", prog, *argv);
			exit(2);
		} else {
			filecomp(fp1, fp2);
			fclose(fp1);
			fclose(fp2);
			exit(0);
		}
	}
}

void filecomp(FILE *fp1, FILE *fp2)
{
	char line1[MAXLINE], line2[MAXLINE];
	char *lp1, *lp2;

	do{
		lp1 = fgets(line1, MAXLINE, fp1);
		lp2 = fgets(line2, MAXLINE, fp2);
		if(lp1 == line1 && lp2 == line2) {
			if(strcmp(line1, line2) != 0) {
				printf("first difference in line\n%s\n", line1);
				lp1 = lp2 = NULL;
			}
		} else if( lp1 != line1 && lp2 == line2 )
			printf("end of first file\n");
		else if( lp1 == line1 && lp2 != line2)
			printf("end of second file\n");
	} while (lp1 == line1 && lp2 == line2);
}
