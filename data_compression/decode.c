//
//  decode.h
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

/* MAIN PROGRAM FOR DECODING */

#include "decode.h"

#include <stdio.h>
#include <stdlib.h>

#include "adaptive_model.h"
#include "bit_input.h"
#include "arithmetic_decode.h"

int arith_decode(unsigned char **output, FILE **file)
{
    start_model();                                  /* Set up other modules     */
    start_inputing_bits();
    start_decoding(file);
    int i;
    for(i = 0; ; i++){                              /* Loop through characters. */
        int ch; int symbol;
        symbol = decode_symbol(cum_freq, file);     /* Decode next symbol       */
        if(symbol == EOF_symbol) {
            break;}                                 /* Exit loop if EOF symbol. */
        ch = index_to_char[symbol];                 /* Translate to a character.*/
        (*output)[i] = ch;                          /* Write that character.    */
        update_model(symbol);                       /* Update the model         */
    }
    return i;                                   /* returns number of decoded characters */
}
