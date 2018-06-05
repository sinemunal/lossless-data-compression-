//
//  adaptive_model.h
//  data_compression_project
//
// Taken from the paper : "ARITHMETIC CODING FOR DATA COMPRESSION",
// by IAN H. WITTEN, RADFORD M. NEAL, and JOHN G. CLEARY.
//

#ifndef adaptive_model_h
#define adaptive_model_h

/* THE SET OF SYMBOLS THAT MAY BE ENCODED */

#define No_of_chars 256                                         /* Number of character symbols */
#define EOF_symbol (No_of_chars + 1)                            /* Index of EOF symbol */

#define No_of_symbols (No_of_chars + 1)                         /* Total number of symbols */


/* TRANSLATION TABLES BETWEEN CHARACTERS AND SYMBOL INDEXES */

extern int char_to_index[No_of_chars];                                 /* To index from character */
extern unsigned char index_to_char[No_of_symbols+1];                   /* To character from index */


/* CUMULATIVE FREQUENCY TABLE */

#define Max_frequency 16383                                     /* Maximum allowed frequency count */
/* 2^14 -1 */
extern int cum_freq[No_of_symbols+1];                                   /* Cumulative symbol frequencies */


void start_model(void);                 /* INITIALIZE THE MODEL.                        */
void update_model(int);                 /* UPDATE THE MODEL TO ACCOUNT FOR A NEW SYMBOL.*/

#endif /* adaptive_model_h */
