 //
//  bit_input.c
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

/* BIT INPUT ROUTINES. */

#include "bit_input.h"

#include <stdlib.h>

#include "arithmetic_coding.h"

/* THE BIT BUFFER. */

static int buffer;                              /* Bits waiting to be input                     */
static int bits_to_go;                          /* Number of bits still in buffer               */
static int garbage_bits;                        /* Number of bits past end-of-life              */

/* INITIALIZE BIT INPUT. */

void start_inputing_bits()
{
    bits_to_go = 0;                             /* Buffer starts out with                       */
    garbage_bits = 0;                           /* no bits in it.                               */
}


/* INPUT A BIT. */

int input_bit(FILE **file)
{
    int t;
    if(bits_to_go == 0){                                /* Read the next byte if no             */
        unsigned char ch = (unsigned char)getc(*file);  // added : 17/5/2018
        buffer = (int)ch;                               /* bits are left in buffer.             */
        int a = buffer;
        a = a;
     
        if(buffer == EOF){
           garbage_bits += 1;                           /* Return arbitrary bits after eof,     */
            if(garbage_bits > Code_value_bits - 2){     /* but check for too many such.         */
                fprintf(stderr, "Bad input file\n");
                exit(-1);
            }
        }
        bits_to_go = 8;
    }
    t = buffer&1;                                       /* Return the next bit from             */
    buffer>>=1;                                         /* the bottom of the byte.              */
    bits_to_go -= 1;
    return t;
}

