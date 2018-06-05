//
//  encode.c
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

/* MAIN PROGRAM FOR ENCODING */

#include "encode.h"

#include <stdlib.h>

#include "adaptive_model.h"
#include "bit_output.h"
#include "arithmetic_encode.h"

void arith_encode(unsigned char **input, FILE **file, int block_len){
    start_model();                              /* Set up other modules */
    start_outputing_bits();
    start_encoding();
    int i;

    for(i = 0; i < block_len; i++){             /* Loop through characters */
        int ch;
        int symbol;
        
        ch = (int)(*input)[i];                  /* Read the next character */
        if(ch == EOF)   break;                  /* Exit loop on end-of-file */
        symbol = char_to_index[ch];             /* Translate to an index */
        encode_symbol(symbol, cum_freq, file);  /* Encode that symbol */
        update_model(symbol);                   /* Update the model */
    }
    encode_symbol(EOF_symbol, cum_freq, file);      /* Encode the EOF symbol */
    done_encoding(file);                            /* Send the last few bits */
    done_outputing_bits(file);
    return;
}
