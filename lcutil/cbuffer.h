/*  Circular buffer
 *  Author:  Nicolas GUILLAUME <ng@ngsoft-fr.com>
 */


/** /!\ cb_offset_t must be able to hold CBUFF_SIZE
 */
#ifndef CBUFF_SIZE
# define CBUFF_SIZE 192
#endif

typedef unsigned char cb_offset_t;



#define EOB ((int)-1)

typedef struct
{
    char data[CBUFF_SIZE];
    cb_offset_t read;
    cb_offset_t write;
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
    b->read = b->write = 0;
}

/** Reset the read pointer */
void cb_reset_read(cbuffer_t * b)
{
    b->read = b->write;
}

/** Blocking version */
char cb_readb(cbuffer_t * b)
{
    int r;
    while( (r = cb_read(b)) == EOB );
    return r;
}

