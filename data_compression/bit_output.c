//
//  bit_output.c
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

/* BIT OUTPUT ROUTINES. */

#include "bit_output.h"

/* THE BIT BUFFER. */

static int buffer;                  /* Bits buffered for output             */
static int bits_to_go;              /* Number of bits free in buffer        */

/* INITIALIZE FOR BIT OUTPUT. */

void start_outputing_bits()
{
    buffer = 0;                     /* Buffer is empty to start with.       */
    bits_to_go = 8;
}

/* OUTPUT A BIT. */

void output_bit(int bit, FILE **file)
{
    buffer >>= 1;                   /* Put bit in top of buffer.            */
    if(bit) buffer |= 0x80;
    bits_to_go -= 1;
    if(bits_to_go == 0){            /* Output buffer if it is now full.     */
        putc(buffer, *file);
        bits_to_go = 8;
    }
    return;
}


/* FLUSH OUT THE LAST BITS. */

void done_outputing_bits(FILE **file)
{
    putc(buffer>>bits_to_go, *file);
    return;
}
