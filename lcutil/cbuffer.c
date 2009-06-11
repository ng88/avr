/*  Circular buffer
 *  Author:  Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include "cbuffer.h"
#include  <stdio.h>
char cb_write(cbuffer_t * b, char c)
{
    int size;
    if(b->write >= b->read)
	size = b->write - b->read;
    else
	size = CBUFF_SIZE - 1 - b->read + b->write;

    if(size == CBUFF_SIZE - 2) // full!
	return 0;

    if(b->write == CBUFF_SIZE - 1)
	b->write = 0;
    else
	b->write++;

    b->data[b->write] = c;
    return 1;
}

int cb_read(cbuffer_t * b)
{
    if(b->read == b->write)
	return EOB;

    if(b->read == CBUFF_SIZE - 1)
	b->read = 0;
    else
	b->read++;

    return b->data[b->read];
}


