#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

/** prints on stdout what we get on stdin, but slowly
 * interval is in µs
 */
int main(int argc, char ** argv)
{
    enum { BURST_SIZE = 128 };

    if(argc < 2)
	return 1;

    int intv = atoi(argv[1]);

    int count = 0;
    int c;
/* send bursts */


    do
    {
	c = fgetc(stdin);
	if(c != EOF)
	{
	    fputc(c, stdout);
	    count++;
	    if(count == BURST_SIZE - 1)
	    {
		fflush(stdout);
		usleep(intv);
		count = 0;
	    }
	}
    }
    while(c != EOF);

    return 0;
}

