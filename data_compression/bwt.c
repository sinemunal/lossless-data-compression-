//
//  bwt.c
//  data_compression_project
//
//  Created by Sinem Unal on 4/23/18.
//  Copyright © 2018 Sinem Unal. All rights reserved.
//

/* BURROWS WHEELER TRANSFORM */

/*  Implementation based on the paper :
    M. Burrows and D. J. Wheeler, “A block-sorting lossless data compression algorithm,”
    Digital Systems Research Center Research Report, Tech. Rep., 1994.
    Also benefiting from a useful dicusssion on the topic at :
    http://michael.dipperstein.com/bwt/index.html
 */

#include "bwt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int comp_size = 1;                      // Used in the comparison function

/* Compare function used by qsort       */
/* to compare each element              */
int lex_compare(const void * a, const void * b)
{
    unsigned char *x1 = *(unsigned char**)a;
    unsigned char *x2 = *(unsigned char**)b;

    return memcmp(x1, x2, comp_size*sizeof(unsigned char));
}

/* Compare function used by qsort       */
/* to compare each element (slower)     */
int lex_compare_2(const void * a, const void * b)
{
    unsigned char *x1 = *(unsigned char**)a;
    unsigned char *x2 = *(unsigned char**)b;
    
    
    for (int tmp_size = comp_size; tmp_size > 0; tmp_size--){
        if(!(*x1 ^ *x2)){
            x1++;
            x2++;
        }
        else if(*x1 < *x2){
            return -1;
        }
        else{
            return 1;
        }
    }
    return 0;
}

/*
 Function   : Applies Burrows Wheeler Transform (BWT) to a given array
 
 Parameters :
 bwt_in     : array of characters to be transformed
 len        : block length, length of the input array
 bwt_out    : array of characters with size len+3, BWT transform of the input array.
    last 3 elements hold the index of the original string after sorting.
    (we store the index int he last three elements to allow a larger block size)
 */
void bwt_encode(unsigned char ** bwt_in, unsigned char ** bwt_out, int len)
{
    unsigned char ** ptr_rotations, *concat_input;                         // Pointer to each element in the input.
    ptr_rotations = (unsigned char**) malloc(len*sizeof(unsigned char*));
    concat_input = (unsigned char*)malloc(2*len*sizeof(unsigned char) + 1);
    memcpy(concat_input, *bwt_in, len*sizeof(unsigned char));
    memcpy(concat_input + len*sizeof(unsigned char), *bwt_in, len*sizeof(unsigned char));
    
    concat_input[2*len] = '\0';                                 // It is for string comparison
                                                                // function used in qsort.
    int i;
    for(i = 0; i < len; i++){
        ptr_rotations[i] = &(concat_input[i]);
    }
    
    comp_size = len;                                            // Used in the comparison function.
    qsort(ptr_rotations, len, sizeof(unsigned char*), lex_compare);      // Cyclic rotated string.
   
    for( i = 0; i < len ; i++){
        (*bwt_out)[i] = *(ptr_rotations[i] + (len-1)*sizeof(unsigned char));    // Populate bwt_out by taking
        if(ptr_rotations[i] == concat_input){                                   // the last character of each rotation
            (*bwt_out)[len] = i/(256*256);                                      // sorted lexicographically.
            (*bwt_out)[len + 1] = (i%(256*256))/256;                            // Find the current index of the
            (*bwt_out)[len + 2] = (i%(256*256))%256;                            // original string.
        }
    }
    free(concat_input);
    concat_input = NULL;

    free(ptr_rotations);
    ptr_rotations = NULL;

    return;
}

/*
 Function   : Applies reverse Burrows Wheeler Transform (BWT) to a given array
 
 Parameters :
 unbwt_in   : array of characters with size len+3 to be reverse transformed
 len        : block length
 unbwt_out  : array of characters with size len, reverse BWT transform of the input array
 */
void bwt_decode(unsigned char ** unbwt_in, unsigned char ** unbwt_out, int len)
{
    int n_pre_chars[No_of_chars] = {0};
    int* n_chars_in_prefix;                                 // ith element holds the number of preceding
    n_chars_in_prefix = (int*) malloc(len*sizeof(int));     // symbols which are the same
    int i, j;                                               // of ith symbol in unbwt_in.
    
    for(i = 0; i < len; i++){
        n_chars_in_prefix[i] = n_pre_chars[(int)(*unbwt_in)[i]];
        n_pre_chars[(int)(*unbwt_in)[i]]++;                 // ith element holds the frequency
                                                            // of ith symbol in unbwt_in so far.
    }
    
    int sum = 0;
    for(i = 0; i < No_of_chars; i++){
        sum = sum + n_pre_chars[i];
        n_pre_chars[i] = sum - n_pre_chars[i];              // ith element holds the number of symbols
    }                                                       // which are less than in the order for
                                                            // ith symbol in unbwt_in.
    i = 256*256*(int)(*unbwt_in)[len];                      // Retrieve the index of the original
    i += 256*(int)(*unbwt_in)[len + 1];                     // array in the sorted list.
    i += (int)(*unbwt_in)[len + 2];
    
    for(j = len - 1; j >= 0; j--){
        (*unbwt_out)[j] = (*unbwt_in)[i];
        i = n_chars_in_prefix[i] + n_pre_chars[(int)(*unbwt_in)[i]];
    }
    free(n_chars_in_prefix);
    n_chars_in_prefix = NULL;
    return;
}
