#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>

/* cc -lm -O2 -pipe -ansi -DONLINE_JUDGE \#101_the_blocks_problem.c */

int main(int argc, char *argv[]) {
	char *buf[1024];
	int no_errors=1;

	/* acceptable inputs:
		1. move <uint> onto <uint>
		2. move <uint> over <uint>
		3. pile <uint> onto <uint>
		4. pile <uint> over <uint>
		5. quit

	"Any command in which a = b or in which a and b are in the same stack of blocks is an illegal command. All illegal commands should be ignored and should have no affect on the configuration of blocks."
	*/

	int state=0; //,a,b;
	while(!(state&4) && (char *)&buf==fgets((char *)&buf,sizeof buf,stdin)) {
		printf("buffer: %s",(char *)&buf);
		char *buf2, *token;
		for( buf2=(char *)&buf; !(state>3 || NULL==(token=strsep(&buf2," \t,")));) {
			printf("token: \"%s\"\n",token);
			if(state<1) state |=
				!strncmp("move",token,4) << 0 |
				!strncmp("pile",token,4) << 1 |
				!strncmp("quit",token,4) << 2 ;
			else {
				state|=8;
			}
		}
		printf("state now %i\n",state);
		if(state && !(state&4)) {
			printf("executing some command; resetting state when complete\n");
			state=0;
		}
	}

	/* for(
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
	)
		if(n%2)
			n=3*n+1;
		else
			n/=2;

	*/
	if(errno || !no_errors) {
		perror(argv[0]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
