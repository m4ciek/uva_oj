#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

/* cc -lm -O2 -pipe -ansi -DONLINE_JUDGE 3n_plus_1.c */

int main(int argc, char *argv[]) {
	char *buf[1024];
	unsigned int no_errors=1,max_cycle,cycle_start,cycle_end,current,n,tmp,cand_len;

	unsigned int lookup[57000];
	unsigned int lookup_s=sizeof lookup>>2;

	for(tmp=lookup_s;tmp--;lookup[tmp]=tmp%2?3*tmp+1:tmp/2);

	for(
		cycle_start=0, cycle_end=0
		; (char *)&buf==fgets((char *)&buf,sizeof buf,stdin) &&
			(2 == sscanf((char *)&buf, "%u %u", &cycle_start, &cycle_end) ||
			(no_errors=0))
		; printf("%d %d %d\n",
			cycle_end==tmp?cycle_end:cycle_start,
			cycle_end==tmp?cycle_start:cycle_end,
			max_cycle
		)
	) for(
		tmp=cycle_start,
		cycle_start=(cycle_end<cycle_start)?cycle_end:cycle_start,
		cycle_end=(cycle_end<tmp)?tmp:cycle_end,
		current=cycle_start-1,
		max_cycle=1
		; current++<cycle_end
		; max_cycle=cand_len>max_cycle?cand_len:max_cycle
	) for(
		n=current, cand_len=1
		; 1 != n
		; cand_len++
	) n=n<lookup_s?lookup[n]:n%2?3*n+1:n/2;


	if(errno || !no_errors) {
		perror(argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
