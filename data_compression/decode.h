//
//  decode.h
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

#ifndef decode_h
#define decode_h

#include <stdio.h>                              // for FILE

int arith_decode(unsigned char **, FILE **);             /* MAIN PROGRAM FOR DECODING */

#endif /* decode_h */
