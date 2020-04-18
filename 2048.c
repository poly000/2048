#include "func.h"

int main(void) {
	time_t now = time(0);
	register int i,j;
	int p[16] = {0};
	register FILE *fp;
	char input;

	initscr(), cbreak(), noecho();

initialize:
	srand(++now);
	i = rand()&15;
	p[i] = 2;
	do
		j = rand()&15;
	while (j == i);
	p[j] = 2;
	printout(&now,p);
body:
	input = (char)getch();
	switch (input) {
		case 'A':
		case 'a':
		case 'W':
		case 'w':
		case 'S':
		case 's':
		case 'D':
		case 'd':
			break;
		case 'r':
		case 'R':
			for (i=0; i<16; i++)
				p[i] = 0;
			goto initialize;
		case 'q':
		case 'Q':
			  endwin();
			return 0;
		case 'l':
		case 'L':
			fp = fopen("save.onk","rb");
			if (fp == 0) {
				printw("load failed!\nhave you already saved?\n");
				goto body;
			}
			fread(p,sizeof(int),(size_t)16,fp);
			fclose(fp);
			printout(&now,p);
			goto body;
		case 'O':
		case 'o':
			fp = fopen("save.onk","wb+");
			if (fp == 0) {
				printw("save failed!\n");
				goto body;
			}
			fwrite(p,sizeof(int),(size_t)16,fp);
			fclose(fp);
			printw("have saved.\n");
			goto body;
		default:
			printw("Invalid Type!\n");
			goto body;
			break;
	}
	movnum(p,input);
	add(p,input);
	newnum(&now,p);
	printout(&now,p);
	goto body;
}
