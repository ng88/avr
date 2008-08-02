#include <stdarg.h>
#include <lcutil/iomin.h>

void mio_puts(const char * s)
{
    while(*s)
	mio_putc(*s++);
}

void mio_printf(const char * s, ...)
{
    enum { NORMAL, WAIT_PC } state = NORMAL;
    va_list ap;
    va_start(ap, s);

    while(*s)
    {
	if(state == NORMAL)
	{
	    if(*s == '%')
		state = WAIT_PC;
	    else
		mio_putc(*s);
	}
	else
	{
	    switch(*s)
	    {
	    case 'n': mio_puts(MIO_CFG_LN_BREAK); break;
	    case 'd': mio_printi(va_arg(ap, int), 10); break;
	    case 'h': mio_printi(va_arg(ap, int), 16); break;
	    case 'o': mio_printi(va_arg(ap, int), 8); break;
	    case 'b': mio_printi(va_arg(ap, int), 2); break;
	    case 's': mio_puts(va_arg(ap, char*)); break;
	    case 'c': mio_putc(va_arg(ap, int)); break;
	    default: mio_putc(*s); break;
	    }
	    state = NORMAL;
	}
	*s++;
    }
    va_end(ap);
}

int main()
{
    char * s = "hohihih"; 
    char c = 'R';
    mio_printf("salut %s %% %n %s %c (%h)(%o)(%b) %n%n", "LO", s, c,
	       12, 87, c);
    return 0;
}






