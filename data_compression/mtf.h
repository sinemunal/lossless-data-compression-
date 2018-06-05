//
//  mtf.h
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


#ifndef mtf_h
#define mtf_h

#ifndef No_of_chars
#define No_of_chars 256
#endif  /* No_of_chars */

void mtf_encode(unsigned char **, unsigned char **, int);
void mtf_decode(unsigned char **, unsigned char **, int);

#endif /* mtf_h */
