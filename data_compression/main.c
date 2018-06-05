//
//  main.c
//  data_compression_project
//
//  Created by Sinem Unal on 5/27/18.
//  Copyright © 2018 Sinem Unal. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "main_scheme.h"

int main(int argc, const char * argv[]) {

    if(argc != 3){
        fprintf(stderr, "Wrong argument is entered\n");
        fprintf(stderr, "For compression enter : -e filename&extension\n");
        fprintf(stderr, "For decompression enter : -d filename&extension\n");
        return -1;
    }
    
    if(strncmp((char*)argv[1],"-e", 2) == 0){
        main_encoding((char*)argv[2]);
    }
    else if(strncmp((char*)argv[1],"-d", 2) == 0){
        main_decoding((char*)argv[2]);
    }
    else{
        fprintf(stderr, "Wrong option is entered.\n");
        fprintf(stderr, "For compression enter : -e filename&extension\n");
        fprintf(stderr, "For decompression enter : -d filename&extension\n");
        return -1;
    }
    
    return 0;
}
