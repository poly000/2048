void newnum(time_t *now,int *p) {
	srand(++*now);
	int i;
	do i = rand()%16;
	while(*(p+i)!=0);
	if (rand()%10==0) // 约1/10几率新的数为4，否则为2
		*(p+i) = 4;
	else
		*(p+i) = 2;
}
