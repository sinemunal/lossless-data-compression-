//
//  bit_output.h
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

#ifndef bit_output_h
#define bit_output_h

#include <stdio.h>                              // for FILE

void start_outputing_bits(void);                /* INITIALIZE FOR BIT OUTPUT.   */
void output_bit(int, FILE **);                  /* OUTPUT A BIT TO FILE         */
void done_outputing_bits(FILE **);              /* FLUSH OUT THE LAST BITS.     */

#endif /* bit_output_h */
