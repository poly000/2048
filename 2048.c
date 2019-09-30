#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

inline static void movnum(int *,char);
inline static void newnum(time_t *,int *);
inline static void printout(int *);
inline static void add(int *,char);

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

inline static void movnum(int *p,char input) {
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

inline static void newnum(time_t *now,int *p) {
	srand(++*now);
	register int i;
	do i = rand()%16;
	while(*(p+i));
	if (!(rand()%10)) {
		*(p+i) = 4;
	} else {
		*(p+i) = 2;
	}
}

inline static void printout(int *p) {
	register int i,j = 0;
	system("cls");
	fprintf(stderr,"use R to reset\n"
		       "use Q to exit\n"
		       "use L to load savedata\n"
		       "use O to save savedata\n"
		       "----------------------------\n\n");
	for(i=0; i<16; i++) {
		if (*(p+i))
			printf(" %5d",*(p+i));
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