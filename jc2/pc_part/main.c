
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


#include "protocol.h"

// the HISTORY_PATH env variable is used to store the command history (optional)
#define HISTORY_MAX  1000

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
    fputc(CMD_GET_SPEED_LIM, dev);
    fflush(dev);
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
    fflush(dev);
}

void set_motor_speed_for_len(char speed, int len)
{
    fputc(CMD_SET_TSPEED, dev);
    fputc(speed, dev);
    fputw(len, dev);
    fflush(dev);
}

void send_program_from_file(char * filename)
{
    FILE * f = fopen(filename, "r");
    if(!f)
	printf("can't open `%s'!\n", filename);
    else
    {
	int r, speed, len;

	// clear current program
	fputc(CMD_PROGRAM_CLEAR, dev);

	while( (r = fscanf(f, "%d %d\n", &speed, &len)) == 2 && r != EOF)
	{
	    printf("adding instruction: speed=%d\t len=%d\n", speed, len);

	    fputc(CMD_PROGRAM_ADD_TSPEED, dev);
	    fputc(speed, dev);
	    fputw(len, dev);
	}

	fflush(dev);
	fclose(f);
    }
}


void start_program()
{
    fputc(CMD_PROGRAM_START, dev);
    fflush(dev);
}

void stop_program()
{
    fputc(CMD_PROGRAM_STOP, dev);
    fflush(dev);
}

void print_help()
{
    puts(
	"help            print this help\n"
	"?               print this help\n"
	"exit            exit\n"
	"quit            exit\n"
	"get limits      retrieve system limits\n"
	"set led n       change led status to n\n"
	"set speed n     change speed to n\n"
	"                see \"get limits\" for bounds\n"
	"set tspeed n t  set speed to n during t time step\n"
	"                see \"get limits\" for bounds\n"
	"load program fn read the text file fn and send the program\n"
	"                that it contains to the target.\n"
	"                file format is one line per instruction with 2 columns:\n"
	"                     speed_value len (like tspeed)\n"
	"start program  start the loaded program.\n"
	"stop program   stop running program.\n"
	);
}

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
    char * histfile = getenv("HISTORY_PATH");
    if(histfile && !histfile[0])
	histfile = NULL;

    using_history();
    if(histfile)
	read_history(histfile);

    enum { MAX_LN = 256 };

    int quit = 0;
    int a1, a2, r;
    char a3[MAX_LN];
    char * l;
    while( !quit && (l = readline(":[MC]> ")) )
    {
	int ignore = 0;

	if(strlen(l) >= MAX_LN)
	    l[MAX_LN - 1] = '\0';
	
	if(!l || l[0] == '\0')
	    ignore = 1;
	else if(l[0] == '?' || !strcmp(l, "help"))
	    print_help();
	else if(!strcmp(l, "quit") || !strcmp(l, "exit"))
	    quit = 1;
	else if(!strcmp(l, "get limits"))
	{
	    if(get_motor_speed_limits(&a1, &a2))
		printf("motor speed limits: [%d, %d]\n", a1, a2);
	    else
		puts("unable to retrieve speed limits!");
	}
	else if( (r = sscanf(l, "set led %d", &a1)) == 1 && r != EOF)
	    set_led(a1);
	else if( (r = sscanf(l, "set speed %d", &a1)) == 1 && r != EOF)
	    set_motor_speed(a1);
	else if( (r = sscanf(l, "set tspeed %d %d", &a1, &a2)) == 2 && r != EOF)
	    set_motor_speed_for_len(a1, a2);
	else if( (r = sscanf(l, "load program %s", a3)) == 1 && r != EOF)
	    send_program_from_file(a3);
	else if(!strcmp(l, "start program"))
	    start_program();
	else if(!strcmp(l, "stop program"))
	    stop_program();
	else
	    puts("unrecognized command, try \"help\"");


	if(!ignore)
	    add_history(l);

	free(l);
    }

    fclose(dev);

    if(histfile)
    {
	write_history(histfile);
	history_truncate_file(histfile, HISTORY_MAX);
    }
    return EXIT_SUCCESS;
}


