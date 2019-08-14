void printout(int *p) {
	register int i,j=0;
	system("cls");
	fprintf(stderr,"use R to reset\n"
		       "use Q to exit\n"
		       "use L to load savedata\n"
		       "use O to save savedata\n"
		       "----------------------------\n\n");
	for(i=0; i<16; i++) {
		if (*(p+i) != 0)
			printf(" %5d",*(p+i));
		else
			printf("      ");
		if (++j == 4) {
			printf("\n\n\n");
			j = 0;
		}
	}
	fprintf(stderr,"----------------------------\n");
}
