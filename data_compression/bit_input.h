//
//  bit_input.h
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

#ifndef bit_input_h
#define bit_input_h

#include <stdio.h>      // For FILE

void start_inputing_bits(void);                 /* INITIALIZE BIT INPUT.    */
int input_bit(FILE **);                         /* INPUT A BIT.             */

#endif /* bit_input_h */
