#include "func.h"

void lost(time_t *now,int p[]) {
	register int input;
	register FILE * fp = NULL;
	register int i,j;
	if (is_lost(p)) {
		printw("You lost!\n");
		do {
			input = getch();
		} while(input != 'r' && input != 'q' &&
		input != 'R' && input != 'Q' && input != 'l'
		&& input != 'L');
		switch (input) {
			case 'R':
			case 'r':
				for (i=0; i<16; i++)
					p[i] = 0;
				srand(++*now);
				i = rand()&15;
				p[i] = 2;
				do
					j = rand()%16;
				while (j == i);
				p[j] = 2;
				printout(now,p);
				break;
			case 'q':
			case 'Q':
				exit(1);
				break;
			case 'l':
			case 'L':
				fp = fopen("save.onk","rb");
				if (fp == 0) {
					printw("load failed!\nhave you already saved?\n");
					break;
				}
				fread(p,sizeof(int),(size_t)16,fp);
				fclose(fp);
				printout(now,p);
				break;
			default:
				break;
		}
	}
}

void movnum(int p[],char input) {
	register int i,j,*k;
  bool next;
	switch (input) {
		case 'W':
		case 'w':
		case 72:
		W:
      next = 0;
			for (i=0; i<4; i++)
				for (j=0; j<3; j++) {
					k = p+(i|(j<<2));
					if (!(*k) && *(k+4)) {
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

void newnum(time_t *now,int p[]) {
	srand(++*now);
	register int i;
	{
		register _Bool full = 1;
		for (i=0; i<16; i++) {
			if (p[i] == 0) {
				full = 0;
				break;
			}
		}
		if (full)
			return;
	}
	do i = rand()&15;
	while(p[i]);
	*(p+i) = rand()%10 ? 2 : 4;
}

void printout(time_t *now,int p[]) {
	register int i,j = 0;
	clear(),
	printw("use R to reset\n"
		       "use Q to exit\n"
		       "use L to load savedata\n"
		       "use O to save savedata\n"
				"----------------------------\n\n");
	for(i=0; i<16; i++) {
		if (p[i])
			printw(" %5d",p[i]);
		else
			printw("      ");
		if (++j > 3) {
			printw("\n\n\n");
			j = 0;
		}
	}
	printw("----------------------------\n");
	lost(now,p);
}

void add(int *p,char input) {
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

bool is_lost(int p[]) {
	register int i;
	{
		register int m,n;
		for (m=p[0],i=1; i<16; i++) {
			n = p[i];
			if (m == n || m == 0)
				return false;
			m = n;
		}
		if (n == 0)
			return false;
	}
	{
		register int num0 = 0;
		register int num1 = 0;
		register int num2 = 0;
		register int num3 = 0;
		for (i=4; i<16; i+=4) {
			if (num0 == p[i]) {
				return false;
			}
			num0 = p[i];
			if (num1 == p[i+1]) {
				return false;
			}
			num1 = p[i+1];
			if (num2 == p[i+2]) {
				return false;
			}
			num2 = p[i+2];
			if (num3 == p[i+3]) {
				return false;
			}
			num3 = p[i+3];
		}
	}
	return true;
}
