//
//  main_scheme.h
//  data_compression_project
//
//  Created by Sinem Unal on 5/17/18.
//  Copyright © 2018 Sinem Unal. All rights reserved.
//

#ifndef main_scheme_h
#define main_scheme_h

#define MAX_BLOCK_LEN   16777215    // should be lower than 16777215
#define MOD_IDX         256         // since we write byte by byte 

int main_encoding(char *);
int main_decoding(char *);

#endif /* main_scheme_h */

