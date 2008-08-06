/*  Circular buffer
 *  Author:  Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include "cbuffer.h"

void cb_write(cbuffer_t * b, char c)
{
    int size;
    if(b->write_ptr >= b->read_ptr)
	size = b->write_ptr - b->read_ptr;
    else
	size = b->last - b->read_ptr + b->write_ptr - b->start;

    if(size == CBUFF_SIZE - 2) // 1 byte lost!
	(void)cb_read(b);

    printf("s=%d\n", size);

    if(b->write_ptr == b->last)
	b->write_ptr = b->start;
    else
	b->write_ptr++;

    *(b->write_ptr) = c;
}

int cb_read(cbuffer_t * b)
{
    if(b->read_ptr == b->write_ptr)
	return EOB;

    if(b->read_ptr == b->last)
	b->read_ptr = b->start;
    else
	b->read_ptr++;

    return *(b->read_ptr);
}



end alculable
read & write devrait etre des short
