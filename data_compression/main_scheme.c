//
//  main_scheme.c
//  data_compression_project
//
//  Created by Sinem Unal on 5/17/18.
//  Copyright © 2018 Sinem Unal. All rights reserved.
//

#include "main_scheme.h"

#include <stdio.h>
#include <stdlib.h>
#include "encode.h"
#include "decode.h"
#include "bwt.h"
#include "mtf.h"


/* MAIN ENCODING SCHEME */
/* Gets the filename with extention as an input             */
/* Applies BWT + MTF + arithmetic encoding                  */
/* Writes the compressed data to a file named "compressed"  */
int main_encoding(char *input_name) {
    FILE *input, *output;           // Output file structure : concatenated encoded blocks.
    int block_len;                  // Each encoding block : mod MOD_IDX of starting index
    int count;                      // of the next encoding block + encoded data of the current block.
    long int cur_size, curr_idx, new_idx;
    
    input = fopen(input_name,"r");
    output = fopen("compressed", "wb");
    if(input == NULL || output == NULL){
        fprintf(stderr,"Cannot open the file!\n");
        return -1;
    }
    // Determine input file size.
    fseek (input, 0, SEEK_END);
    cur_size = ftell(input)/ sizeof(char);
    fseek (input, 0, SEEK_SET);
    
    putc(0, output);                 // Will hold the starting index of the first encoded block in the output file.
    
    unsigned char *input_buf, *tmp_buf;
    input_buf = (unsigned char*)malloc(MAX_BLOCK_LEN + 3);
    tmp_buf = (unsigned char*)malloc(MAX_BLOCK_LEN + 3);
    
    if(input_buf == NULL || tmp_buf == NULL){
        fprintf(stderr, "Memory allocation error!\n");
        return -1;
    }
    while(cur_size > 0){
        // Determine the current block length.
        block_len = cur_size > MAX_BLOCK_LEN ? MAX_BLOCK_LEN : cur_size;
        // Read the data.
        count = fread(input_buf, sizeof(unsigned char), block_len, input);
        if(count != block_len){
            fprintf(stderr,"Read file error!\n");
            // Free memory.
            free(tmp_buf);
            free(input);
            // Close files.
            fclose(input);
            fclose(output);
            return -1;
        }
        // Apply BWT.
        bwt_encode(&input_buf, &tmp_buf, block_len);
        
        // Apply MTF.
        mtf_encode(&tmp_buf, &input_buf, block_len+3);
        
        curr_idx = ftell(output)/ sizeof(char);     // index of current element in output file
        
        // Apply arithmetic encoding.
        arith_encode(&input_buf, &output, block_len + 3); //  
        new_idx = ftell(output)/ sizeof(char);      // index of current element after encoding in output file
        
        // Go back and insert the encoded block length.
        fseek (output, curr_idx - 1, SEEK_SET);
        putc(((new_idx) % MOD_IDX), output);
        fseek(output, new_idx, SEEK_SET);
        
        // Update the uncoded file size
        cur_size -= block_len;
        if(cur_size > 0){
            putc(0, output);     // This will hold the starting index of the next encoded block in the output file.
        }
        //printf("uncoded file size in characters : %li \n", cur_size);
    }
    // Free memory.
    free(tmp_buf);
    free(input_buf);
    // Close files.
    fclose(input);
    fclose(output);
    
    return 0;
}

/* MAIN DECODING SCHEME */
/* Gets the filename with extention as an input                 */
/* Applies arithmetic decoding  + reverse MTF + reverse BWT     */
/* Writes the decompressed data to a file named "decompressed"  */
int main_decoding(char *input_name )
{
    FILE *input, *output;           // Input file structure : concatenated encoded blocks.
    int block_len;                  // Each encoding block : mod MOD_IDX of starting index
                                    // of the next encoding block + encoded data of the current block
    long int file_size;             // current size of the uncoded file.
    input = fopen(input_name,"r");
    output = fopen("decompressed", "wb");
    if(input == NULL || output == NULL){
        fprintf(stderr,"Cannot open the file!\n");
        return -1;
    }
    // Determine input file size.
    fseek (input, 0, SEEK_END);
    file_size = ftell(input)/ sizeof(char);
    fseek (input, 0, SEEK_SET);
    
    unsigned char *input_buf, *tmp_buf;
    input_buf = (unsigned char*)malloc(MAX_BLOCK_LEN + 3);
    tmp_buf = (unsigned char*)malloc(MAX_BLOCK_LEN + 3);
    if(input_buf == NULL || tmp_buf == NULL){
        fprintf(stderr, "Memory allocation error!\n");
        return -1;
    }
    
    while(ftell(input)/ sizeof(char) < file_size){
        // Find the starting index of the next block.
        long int next_idx, start_idx, curr_idx;
        start_idx = getc(input);
        //printf("index of current element in file : %li\n ", ftell(input)/ sizeof(char));
        
        // Apply arithmetic decoding.
        block_len = arith_decode(&input_buf, &input);
        
        // Calculate the starting index of the next block.
        curr_idx = ftell(input)/ sizeof(char);
        
        // We know that curr_idx is greater than or equal to the actual index that
        // we need to start encoding.
        if(curr_idx < file_size){                                               // more blocks to encode
            next_idx = ((int)(curr_idx / MOD_IDX))*MOD_IDX + start_idx;
            if(next_idx > curr_idx){                                            // to eliminate the cases like
                next_idx = ((int)(curr_idx / MOD_IDX) - 1)*MOD_IDX + start_idx; // actual index MOD_IDX -1 and current
            }                                                                   // index  MOD_IDX
            fseek(input, next_idx, SEEK_SET);
        }
        
        //printf("index of adjusted index after arith decoding : %li\n ", ftell(input)/ sizeof(char));
        //printf("Current block length is %d\n", block_len);
        
        // Apply  reverse MTF.
        mtf_decode(&input_buf, &tmp_buf, block_len);
        
        // Apply  reverse BWT.
        bwt_decode(&tmp_buf, &input_buf, block_len - 3);
        
        // Write the output.
        fwrite(input_buf, sizeof(unsigned char), block_len -3, output);
    }
    // Free memory.
    free(tmp_buf);
    free(input_buf);
    // Close files.
    fclose(input);
    fclose(output);
    
    return 0;
}
