//
//  map.h
//  cmap
//
//  Created by Timothy Quang-Tin Le on 8/19/18.
//  Copyright © 2018 Timothy Quang-Tin Le. All rights reserved.
//

#ifndef map_h
#define map_h

#include <stdio.h>
#include <stdbool.h>

#define MAP_NUM_BUCKETS 16 //based on default setting in Java
                           //https://docs.oracle.com/javase/8/docs/api/java/util/HashMap.html

typedef struct map_elem map_elem;
typedef struct map Map;

Map *map_init();

//If a string is the map or key, include +1 for the null terminator in the size
void map_put(Map *map, const void *key, const void *val,
             size_t key_sz, size_t val_sz);

const void *map_get(Map *map, const void *key, size_t key_sz);

void map_remove(Map *map, const void *key, size_t key_sz);

void map_free(Map *map);

size_t map_num_elems(Map *map);

void map_print_distrib(Map *map);

//should only call if all keys and vals in map are strs or ints
//"true" for all strs and "false" for all ints
void map_print_str_int_elems(Map *map, bool all_strs);

#endif /* map_h */
