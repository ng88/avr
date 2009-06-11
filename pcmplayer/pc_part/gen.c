#include <stdio.h>
#include <stdlib.h>


/** prints the argument value continously
 */
int main(int argc, char ** argv)
{
    if(argc < 2)
	return 1;

    unsigned char value = atoi(argv[1]);
    printf("Sending %u...\n", value);

    while(1)
	putchar(value);

    return 0;
}

