//
//  arithmetic_decode.h
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

#ifndef arithmetic_decode_h
#define arithmetic_decode_h

#include <stdio.h>                                      // for FILE

void start_decoding(FILE **file);                       /* START DECODING A STREAM OF SYMBOLS.  */
int decode_symbol(int[], FILE **file);                  /* DECODE THE NEXT SYMBOL               */

#endif /* arithmetic_decode_h */
