
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>


#include "protocol.h"

static FILE * dev;


/** put word */
void fputw(unsigned short w, FILE * d)
{
    union
    {
	unsigned short  int vint;
	char                vbyte[2];
    } vs;
    vs.vint = w;
    fputc(vs.vbyte[0], d);
    fputc(vs.vbyte[1], d);
}


void set_led(char s)
{
    fputc(CMD_SET_LED, dev);
    fputc(s, dev);
    fflush(dev);
}

/** Return non-zero on success*/
int get_motor_speed_limits(int * minl, int * maxl)
{
    *minl=60;*maxl=127;    return 1;

    fputc(CMD_GET_SPEED_LIM, dev);
    if(fgetc(dev) == CMD_GET_SPEED_LIM_ANS)
    {
	*minl = fgetc(dev);
	*maxl = fgetc(dev);
	return 1;
    }
    return 0;
}

void set_motor_speed(char speed)
{
    fputc(CMD_SET_SPEED, dev);
    fputc(speed, dev);
}

void set_motor_speed_for_len(char speed, int len)
{
    fputc(CMD_SET_TSPEED, dev);
    fputc(speed, dev);
    fputw(len, dev);
}

/** prints the argument value continously
 */
int main(int argc, char ** argv)
{
    if(argc < 2)
    {
	fputs("one argument is required: serial device path.\n", stderr);
	return EXIT_FAILURE;
    }
    
    dev = fopen(argv[1], "r+");
    if(!dev)
    {
	fprintf(stderr, "unable to open device `%s'\n", argv[1]);
	return EXIT_FAILURE;
    }


    /** request speed limits */
    int min_speed, max_speed;
    if(get_motor_speed_limits(&min_speed, &max_speed))
    {
	printf("motor speed limits: [%d, %d]\n", min_speed, max_speed);
	set_led(1);

	char * l;
	while( (l = readline(":[MC]> ")) )
	{

	    free(l);
	}

    }
    else
	printf("unable to get speed limits\n");

    fclose(dev);

    return EXIT_SUCCESS;
}


