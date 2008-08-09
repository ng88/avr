/*  Circular buffer
 *  Author:  Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */

#ifndef CBUFF_SIZE
# define CBUFF_SIZE 128
#endif

#define EOB ((int)-1)

typedef struct
{
    char start[CBUFF_SIZE];
    char * read_ptr;
    char * write_ptr;
    char * last;
} cbuffer_t;




void cb_write(cbuffer_t * b, char c);

/** Read a char from b, if no char is available,
 * return EOB.
 */
int cb_read(cbuffer_t * b);



#if !defined(__DOXYGEN__)
static inline void cb_reset_read(cbuffer_t * __b) __attribute__((always_inline));
static inline char cb_readb(cbuffer_t * __b) __attribute__((always_inline));
static inline void cb_init(cbuffer_t * __b) __attribute__((always_inline));
#endif

/** Init buffer */
void cb_init(cbuffer_t * b)
{
    b->read_ptr = b->write_ptr = b->start - 1;
    b->last = b->start + CBUFF_SIZE - 1;
}

/** Reset the read pointer */
void cb_reset_read(cbuffer_t * b)
{
    b->read_ptr = b->write_ptr;
}

/** Blocking version */
char cb_readb(cbuffer_t * b)
{
    int r;
    while( (r = cb_read(b)) == EOB );
    return r;
}

