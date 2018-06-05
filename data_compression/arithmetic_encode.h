//
//  arithmetic_encode.h
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

#ifndef arithmetic_encode_h
#define arithmetic_encode_h
#include<stdio.h>

void start_encoding(void);                  /*  START ENCODING A STREAM OF SYMBOLS  */
void encode_symbol(int, int [], FILE **);   /* ENCODE A SYMBOL                      */
void done_encoding(FILE **);                /* FINISH ENCODING THE STREAM           */

#endif /* arithmetic_encode_h */
