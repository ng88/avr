#include <stdarg.h>
#include <stdlib.h>
#include <lcutil/string.h>

	
void itoa(int value, char * str, int base)
{
    static char num[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    char* wstr = str;
    int sign;
    div_t res;
	
    if (base<2 || base>35)
    {
	*wstr = '\0';
	return;
    }
	
    if((sign = value) < 0)
	value = -value;

    do
    {
	res = div(value, base);
	*wstr++ = num[res.rem];
	
    }
    while(value = res.quot);
	
    if(sign<0)
	*wstr++ = '-';
    
    *wstr = '\0';
    strreverse(str, wstr - 1);
}





