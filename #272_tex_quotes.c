#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	char buf[80];

	int bigbuf_s, this_strlen;
	char *bigbuf, **qbufs;

	for(
		bigbuf_s=0, bigbuf=NULL
		; (char *)&buf == fgets((char *)&buf, sizeof buf, stdin)
		; memcpy(&bigbuf[bigbuf_s-this_strlen], (char *)&buf, this_strlen)
	) if(NULL==(
		bigbuf=realloc(bigbuf, bigbuf_s += (
			this_strlen=strnlen((char *)&buf, sizeof buf)
		))
	)) {
		perror(argv[0]);
		return EXIT_FAILURE;
	}

	if(NULL==bigbuf)
		bigbuf=(char *)&buf;

	if(NULL==(qbufs=malloc(sizeof(char*)))) {
		perror(argv[0]);
		return EXIT_FAILURE;
	}

	int substr,walk;

	for(
		substr=0,walk=0,qbufs[0]=bigbuf;
		walk < bigbuf_s;
	) if('"'==bigbuf[walk++] && NULL!=(qbufs=realloc(qbufs,(++substr+1)*sizeof(char *)))) {
		(qbufs[substr]=&bigbuf[walk])[-1]='\0';
		printf(substr%2 ?"%s" :"``%s''", qbufs[substr-1]);
	} else if(NULL==qbufs) {
		perror(argv[0]);
		return EXIT_FAILURE;
	}

	if(bigbuf_s) {
		if(bigbuf[bigbuf_s-1])
			printf("%.*s",bigbuf_s-(int)(qbufs[substr]-bigbuf),qbufs[substr]);
		free(bigbuf);
	}

	free(qbufs);

	return 0;
}
