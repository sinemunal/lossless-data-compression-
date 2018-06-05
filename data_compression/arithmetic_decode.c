//
//  arithmetic_decode.c
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

/* ARITHMETIC DECODING ALGORTIHM */

#include "arithmetic_decode.h"

#include "arithmetic_coding.h"
#include "bit_input.h"

/* CURRENT STATE OF THE DECODING. */

static code_value value;                                /* Currently seen code value            */
static code_value low, high;                            /* Ends of current code region          */

/* START DECODING A STREAM OF SYMBOLS. */

void start_decoding(FILE **file)
{
    int i;
    value = 0;                                          /* Input bits to fill the code value    */
    for(i = 1; i <=Code_value_bits; i++){
        value = 2*value+input_bit(file);
    }
    low = 0;                                            /* Full code range                      */
    high = Top_value;
}

/* DECODE THE NEXT SYMBOL */

int decode_symbol(int cum_freq[], FILE **file)          /* Cumulative symbol frequencies        */
{
    long range;                                         /* Size of current code region          */
    int cum;                                            /* Cumulative frequency calculated      */
    int symbol;                                         /* Symbol decoded                       */
    range = (long) (high - low) + 1;
    cum = (((long)(value - low)+ 1)*cum_freq[0] - 1)/ range;    /* Find cum freq for value.     */
    for(symbol = 1; cum_freq[symbol] > cum; symbol++);          /* Then find symbol.            */
    high = low + (range*cum_freq[symbol - 1])/ cum_freq[0] - 1; /* Narrow the code region to    */
    low = low + (range*cum_freq[symbol])/ cum_freq[0];          /* that allotted to this symbol.*/
   
    for(;;){                                                    /* Loop to get rid of bits.     */
        if(high < Half){
            /* nothing */                                       /* Expand low half.             */
        }
        else if (low >= Half){                                  /* Expand high half.            */
            value -= Half;
            low -= Half;                                        /* Subtract offset to top.      */
            high -= Half;
        }
        else if(low >= First_qtr && high < Third_qtr){          /* Expand middle half.          */
            value -= First_qtr;
            low -= First_qtr;                                   /* Subtract offset to middle.   */
            high -= First_qtr;
        }
        else break;                                             /* Otherwise exit loop.         */
        low = 2*low;
        high = 2*high + 1;                                      /* Scale up code range.         */
        value = 2*value + input_bit(file);                      /* Move in next input bit.      */
    }
    return symbol;
}
