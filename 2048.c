#include "2048.h"

extern void movnum(int *,char);
extern void newnum(time_t *,int *);
extern void printout(int *);
extern void add(int *,char);

int main(void) {
	time_t now = time(0);
	register int i,j,k;
	register int *p=(int *)malloc(sizeof(int)*16),*q=(int *)malloc(sizeof(int)*16);
	FILE *fp;
	if (p == 0 || q == 0)
		return 1;
	for (i=0; i<16; i++)
		*(p+i) = 0;
	char input;
a:
	srand(++now);
	i = rand()%16;
	*(p+i) = 2;
	do
		j = rand()%16;
	while (j == i);
	*(p+j) = 2;
	printout(p);
b:
	srand(++now);
	k = rand();
	for (i=0; i<16; i++)
		*(q+i) = *(p+i)+k;
	input = (char)getch();
	switch (input) {
		case -32:
			input = (char)getch();
			break;
		case 'r':
		case 'R':
			for (i=0; i<16; i++)
				*(p+i) = 0;
			goto a;
		case 'q':
		case 'Q':
			free(p);
			free(q);
			return 0;
		case 'l':
		case 'L':
			fp = fopen("save.onk","rb");
			if (fp == 0) {
				fprintf(stderr,"load failed!\nhave you already saved?\n");
				goto b;
			}
			fread(p,sizeof(int),16,fp);
			fclose(fp);
			printout(p);
			goto b;
		case 'O':
		case 'o':
			fp = fopen("save.onk","wb+");
			if (fp == 0) {
				fprintf(stderr,"save failed!\n");
				goto b;
			}
			fwrite(p,sizeof(int),16,fp);
			fclose(fp);
			fprintf(stderr,"have saved.\n");
			goto b;
		default:
			fprintf(stderr,"Invalid Type!\n");
			break;
	}
	for (i=0; i<16; i++) {
		if (*(q+i) != *(p+i)+k) {
			fprintf(stderr,"DO NOT CHEAT! (PRESS A KEY TO EXIT)\n");
			getch();
			return 1;
		}
	}
	movnum(p,input);
	add(p,input);
	for (j=0,i=0; i<16; i++)
		if (*(q+i) == *(p+i)+k)
			j++;
	if (j != 16) {
		newnum(&now,p);
		printout(p);
	}
	goto b;
}
