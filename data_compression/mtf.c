//
//  mtf.c
//  data_compression_project
//
//  Created by Sinem Unal on 4/23/18.
//  Copyright © 2018 Sinem Unal. All rights reserved.
//

/* MOVE TO FRONT CODING */

/*  Implementation based on the paper :
    M. Burrows and D. J. Wheeler, “A block-sorting lossless data compression algorithm,”
    Digital Systems Research Center Research Report, Tech. Rep., 1994.
    Also benefiting from a useful dicusssion on the topic at :
    http://michael.dipperstein.com/bwt/index.html
 */



#include "mtf.h"

/* This function moves the element in arr with src_idx to           */
/* the beginning and shift the other elements until src_idx by one  */
void move_idx(unsigned char *arr, int src_idx){
    char tmp = arr[src_idx];
    int i;
    for(i = src_idx; i > 0; i--){
        arr[i] = arr[i-1];
    }
    arr[0] = tmp;
    return;
}

/* This function returns the index of the elem if                   */
/* elem is in arr. Otherwise return -1.                             */
int find_idx(unsigned char *arr, int len, unsigned char elem){
    int i;
    for(i = 0; i < len; i++){
        if(arr[i] == elem){
            return i;
        }
    }
    return -1;
}

/*
 Function   : Applies Move to Front (MTF) encoding to a given array
 
 Parameters :
 mtf_in     : array of characters to be transformed
 len        : length of the input array
 mtf_out    : array of characters, MTF encoded
 */
void mtf_encode(unsigned char **mtf_in, unsigned char **mtf_out, int len)
{
    unsigned char char_list[No_of_chars];           // List holding all possible characters.
                                                    // Each character appears only once.
    int i, idx;
    for(i = 0; i < No_of_chars; i++){               // Create character list.
        char_list[i] = (unsigned char)i;
    }
    
    for(i = 0; i < len; i++){                                   // For each character find its
        idx = find_idx(char_list, No_of_chars, (*mtf_in)[i]);   // current position in
        (*mtf_out)[i] = (unsigned char)idx;                     // the character list, output the position.
        move_idx(char_list, idx);                               // Then update the character list.
    }
    return;
}


/*
 Function   : Applies Move to Front (MTF) decoding to a given array
 
 Parameters :
 unmtf_in   : array of characters to be decoded
 len        : length of the input array
 unmtf_out  : array of characters, MTF decoded
 */
void mtf_decode(unsigned char **unmtf_in, unsigned char **unmtf_out, int len)
{
    unsigned char char_list[No_of_chars];           // List holding all possible characters.//
    int i;                                          // Each character appears only once.    //
    for(i = 0; i < No_of_chars; i++){               // Create character list.               //
        char_list[i] = (unsigned char)i;
    }
    
    for(i = 0; i < len; i++){                       // Output the character in character    //
        (*unmtf_out)[i] = char_list[(int)(*unmtf_in)[i]]; // list given by the index        //
        move_idx(char_list, (int)(*unmtf_in)[i]);   // in input. Update the character list. //
    }
    return;
}
