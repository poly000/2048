#include "2048.h"

void movnum(int *p,char input) {
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
					k = p+i+(j<<2);
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
				for (j=2; j; j--) {
					k = p+i+(j<<2);
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
					k = p+(i<<2)+j;
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
				for (j=2; j; j--) {
					k = p+(i<<2)+j;
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

void newnum(time_t *now,int *p) {
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

void printout(int *p) {
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

void add(int *p,char input) {
	register int i,j,*k;
	switch (input) {
		case 'W':
		case 'w':
		case 72:
			for (i=0; i<4; i++)
				for (j=0; j<3; j++) {
					k = p+i+(j<<2);
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
				for (j=2; j; j--) {
					k = p+i+(j<<2);
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
					k = p+(i<<2)+j;
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
				for (j=2; j; j--) {
					k = p+(i<<2)+j;
					if (*k & *(k+1)) {
						*(k+1) <<= 1;
						*k = 0;
					}
				}
			break;
	}
	movnum(p,input);
}
