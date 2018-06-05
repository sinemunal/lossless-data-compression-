//
//  arithmetic_encode.c
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

/* ARITHMETIC ENCODING ALGORITHM */

#include "arithmetic_encode.h"

#include "arithmetic_coding.h"
#include "bit_output.h"

static void bit_plus_follow(int, FILE **);              /* Routine that follows */

/* CURRENT STATE OF THE ENCODING */

static code_value low, high;                            /* End of the current code region */
static long bits_to_follow;                             /* Number of opposite bits to output after
                                                         the next bit */

/*  START ENCODING A STREAM OF SYMBOLS */

void start_encoding()
{
    low = 0;                                            /* Full code range          */
    high = Top_value;
    bits_to_follow = 0;                                 /* No bits to follow next   */
}


/* ENCODE A SYMBOL */

void encode_symbol(int symbol, int cum_freq[], FILE **file)     /* Cumulative symbol frequencies    */
{
    long range;                                                 /* Size of the current code region  */
    range = (long)(high - low) + 1;
    high = low + (range*cum_freq[symbol - 1])/cum_freq[0] - 1;  /* Narrow the code region           */
                                                                /* to that allotted to this symbol  */
    low = low + (range*cum_freq[symbol])/cum_freq[0];
    
    for(;;){                                            /* Loop to output bits      */
        if(high < Half){
            bit_plus_follow(0, file);                   /* Output 0 if in low half  */
        }
        else if(low >= Half){                           /* Output 1 if in high half */
            bit_plus_follow(1, file);
            low -= Half;
            high -= Half;                               /* Subtract offset to top   */
        }
        else if(low >= First_qtr && high < Third_qtr ){ /* Output an opposite bit   */
                                                        /* later in the middle half */
            bits_to_follow += 1;
            low -= First_qtr;                           /* Subtract offset to middle*/
            high -= First_qtr;
        }
        else break;                                     /* Otherwise exit loop      */
        low = 2*low;
        high = 2*high + 1;                              /* Scale up code range      */
    }
}

/* FINISH ENCODING THE STREAM */

void done_encoding(FILE **file)
{
    bits_to_follow += 1;                                /* Output two bits that select  */
    if(low < First_qtr)                                 /* the quarter that the current */
        bit_plus_follow(0, file);                       /* code range contains          */
    else
        bit_plus_follow(1, file);
}

/* OUTPUT BITS PLUS FOLLOWING OPPOSITE BITS */

static void bit_plus_follow(int bit, FILE **file){
    output_bit(bit, file);                              /* Output the bit.              */
    while(bits_to_follow > 0){
        output_bit(!bit, file);                         /* Output bits_to_follow        */
        bits_to_follow -=1;                             /* opposite bits. Set           */
    }                                                   /* bits_to_follow to zero.      */
}
