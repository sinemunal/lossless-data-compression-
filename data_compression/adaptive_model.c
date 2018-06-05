//
//  adaptive_model.c
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

/* THE ADAPTIVE SOURCE MODEL  */

#include "adaptive_model.h"

int freq[No_of_symbols + 1];                    /* Symbol frequencies.                      */

int char_to_index[No_of_chars];
unsigned char index_to_char[No_of_symbols+1];
int cum_freq[No_of_symbols+1]; 

/* INITIALIZE THE MODEL. */

void start_model()
{
    int i;
    for(i = 0; i < No_of_chars; i++){           /* Set up tables that translate between     */
        char_to_index[i] = i + 1;               /* symbol indexes and characters.           */
        index_to_char[i + 1] = i;
    }
    for(i = 0; i <= No_of_symbols; i++){        /* Set up initial frequency counts to be    */
        freq[i] = 1;                            /* one for all symbols.                     */
        cum_freq[i] = No_of_symbols - i;
    }
    freq[0] = 0;                                /* Freq[0] must not be thr same as freq[1]. */
}


/* UPDATE THE MODEL TO ACCOUNT FOR A NEW SYMBOL. */

void update_model(int symbol)                   /* Index of new symbol                      */
{
    int i;                                      /* New index for symbol                     */
    if(cum_freq[0] == Max_frequency){           /* See if frequency counts are              */
        int cum;                                /* at their maximum.                        */
        cum = 0;
        for(i = No_of_symbols; i >= 0; i--){    /* If so, halve all the counts (keeping     */
            freq[i] = (freq[i] + 1)/2;          /* them non-zero).                          */
            cum_freq[i] = cum;
            cum += freq[i];
        }
    }
    for(i = symbol; freq[i] == freq[i - 1]; i--);   /* Find symbols's new index.            */
    if(i < symbol){
        int ch_i, ch_symbol;
        ch_i = index_to_char[i];                    /* Update the translateion tables if    */
        ch_symbol = index_to_char[symbol];          /* the symbol has moved.                */
        index_to_char[i] = ch_symbol;
        index_to_char[symbol] = ch_i;
        char_to_index[ch_i] = symbol;
        char_to_index[ch_symbol] = i;
    }
    freq[i] += 1;                                   /* Increment the frequency count for    */
    while( i > 0){                                  /* the symbol and update the            */
        i -= 1;                                     /* cumulative frequencies.              */
        cum_freq[i] += 1;
    }
}
