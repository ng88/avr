/*  Circular buffer
 *  Author:  Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#include "cbuffer.h"

void cb_write(cbuffer_t * b, char c)
{
    int size;
    if(b->write >= b->read)
	size = b->write - b->read;
    else
	size = CBUFF_SIZE - 1 - b->read + b->write;

    if(size == CBUFF_SIZE - 2) // 1 byte lost!
	(void)cb_read(b);

    if(b->write == CBUFF_SIZE - 1)
	b->write = 0;
    else
	b->write++;

    b->data[b->write] = c;
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

