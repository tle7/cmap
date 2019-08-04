//
//  hash.c
//  cmap
//
//  Created by Timothy Quang-Tin Le on 8/31/18.
//  Copyright © 2018 Timothy Quang-Tin Le. All rights reserved.
//
//  The following hash function is adapted from: https://www.strchr.com/hash_functions
//  INIT_VALUE of 0 and MULTIPLIER of 31 is based on Kernighan and Ritchie's function
//  referenced in the strchr.com article

#include "hash.h"

#define INIT_VALUE 0
#define MULTIPLIER 31

//returns a hash value that must be modded by the number of buckets
unsigned int hash(const char *data, size_t data_sz) {
    unsigned int hash = INIT_VALUE;
    for (unsigned int i = 0; i < data_sz; i++)
        hash = (MULTIPLIER * hash) + data[i];
    return hash; //must be used with a mod of the number of buckets
}