#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#define JUST_FOR_FUN 0

inline static void movnum(int [],char);
inline static void newnum(time_t *,int []);
inline static void printout(int []);
inline static void add(int [],char);

int main(void) {
	time_t now = time(0);
	register int i,j;
	int p[16] = {0},q[16];
	register FILE *fp;
	char input;
initialize:
	srand(++now);
	i = rand()%16;
	p[i] = 2;
	do
		j = rand()%16;
	while (j == i);
	p[j] = 2;
	printout(p);
body:
	for (i=0; i<16; i++) {
		q[i] = p[i];
	}
	input = (char)getch();
	switch (input) {
		case -32:
			input = (char)getch();
			break;
		case 'r':
		case 'R':
			for (i=0; i<16; i++)
				p[i] = 0;
			goto initialize;
		case 'q':
		case 'Q':
			return 0;
		case 'l':
		case 'L':
			fp = fopen("save.onk","rb");
			if (fp == 0) {
				fprintf(stderr,"load failed!\nhave you already saved?\n");
				goto body;
			}
			fread(p,sizeof(int),16,fp);
			fclose(fp);
			printout(p);
			goto body;
		case 'O':
		case 'o':
			fp = fopen("save.onk","wb+");
			if (fp == 0) {
				fprintf(stderr,"save failed!\n");
				goto body;
			}
			fwrite(p,sizeof(int),16,fp);
			fclose(fp);
			fprintf(stderr,"have saved.\n");
			goto body;
		default:
			fprintf(stderr,"Invalid Type!\n");
			break;
	}
	movnum(p,input);
	add(p,input);
	for (j=0,i=0; i<16; i++)
		if (q[i] == p[i])
			j++;
	if (j != 16) {
		newnum(&now,p);
		printout(p);
	}
	goto body;
}

inline static void movnum(int p[],char input) {
	register int i,j,*k;
  _Bool next;
	switch (input) {
		case 'W':
		case 'w':
		case 72:
		W:
      next = 0;
			for (i=0; i<4; i++)
				for (j=0; j<3; j++) {
					k = p+(i|(j<<2));
					if (!(*k) && *(k+4)) { //如果“移动”时前方为0，移动并再次循环判断，否则打断循环
						*k = *(k+4);
						*(k+4) = 0;
						next = 1;
					}
				}
   			if (next)
     				goto W;
			break;
		case 'S':
		case 's':
		case 80:
		S:
      next = 0;
			for (i=0; i<4; i++)
				for (j=2; j>=0; j--) {
					k = p+(i|(j<<2));
					if(*k && !(*(k+4))) {
						*(k+4) = *k;
						*k = 0;
						next = 1;
					}
				}
			if (next)
				goto S;
			break;
		case 'a':
		case 'A':
		case 75:
		A:
      next = 0;
			for (i=0; i<4; i++)
				for (j=0; j<3; j++) {
					k = p+((i<<2)|j);
					if (!(*k) && *(k+1)) {
						*k = *(k+1);
						*(k+1) = 0;
						next = 1;
					}
				}
			if (next)
				goto A;
			break;
		case 'D':
		case 'd':
		case 77:
		D:
      next = 0;
			for (i=0; i<4; i++)
				for (j=2; j>=0; j--) {
					k = p+((i<<2)|j);
					if(*k && !(*(k+1))) {
						*(k+1) = *k;
						*k = 0;
						next = 1;
					}
				}
      			if (next)
				goto D;
			break;
	}
}

inline static void newnum(time_t *now,int p[]) {
	srand(++*now);
	register int i;
	do i = rand()%16;
	while(p[i]);
	*(p+i) = rand()%10 ? 2 : 4;
}

inline static void printout(int p[]) {
	register int i,j = 0;
	system("cls");
	fprintf(stderr,"use R to reset\n"
		       "use Q to exit\n"
		       "use L to load savedata\n"
		       "use O to save savedata\n"
					 "----------------------------\n\n");
	for(i=0; i<16; i++) {
		if (p[i])
			printf(" %5d",p[i]);
		else
			printf("      ");
		if (++j & 4) {
			printf("\n\n\n");
			j = 0;
		}
	}
	fprintf(stderr,"----------------------------\n");
}

inline static void add(int *p,char input) {
	register int i,j,*k;
	switch (input) {
		case 'W':
		case 'w':
		case 72:
			for (i=0; i<4; i++)
				for (j=0; j<3; j++) {
					k = p+(i|(j<<2));
					if (*k & *(k+4)) {
						*k <<= 1;
						*(k+4) = 0;
					}
				}
			break;
		case 'S':
		case 's':
		case 80:
			for (i=0; i<4; i++)
				for (j=2; j>=0; j--) {
					k = p+(i|(j<<2));
					if (*k & *(k+4)) {
						*(k+4) <<= 1;
						*k = 0;
					}
				}
			break;
		case 'A':
		case 'a':
		case 75:
			for (i=0; i<4; i++)
				for (j=0; j<3; j++) {
					k = p+((i<<2)|j);
					if (*k & *(k+1)) {
						*k <<= 1;
						*(k+1) = 0;
					}
				}
			break;
		case 'D':
		case 'd':
		case 77:
			for (i=0; i<4; i++)
				for (j=2; j>=0; j--) {
					k = p+((i<<2)|j);
					if (*k & *(k+1)) {
						*(k+1) <<= 1;
						*k = 0;
					}
				}
			break;
	}
	movnum(p,input);
}
