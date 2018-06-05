//
//  encode.h
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

#ifndef encode_h
#define encode_h
#include <stdio.h>                      // For FILE

void arith_encode(unsigned char **, FILE **, int);             /* MAIN PROGRAM FOR ENCODING */

#endif /* encode_h */
