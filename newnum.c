void newnum(time_t *now,int *p) {
	srand(++*now);
	register int i;
	do i = rand()%16;
	while(*(p+i)!=0);
	if (rand()%10==0)
		*(p+i) = 4;
	else
		*(p+i) = 2;
}
