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

#define MAP_ARRAY_SZ 1

typedef struct map_elem {
    void *key;
    size_t key_sz;
    void *val;
    size_t val_sz;
    
    struct map_elem *next;
    struct map_elem *prev;
} map_elem;

typedef struct {
    map_elem *elem_arr[MAP_ARRAY_SZ];
} Map;

Map *init_map();

//If a string is the map or key, include the null terminator in the size
void map_put(Map *map, void *key, void *val, size_t key_sz, size_t val_sz);

const void *map_get(Map *map, void *key, size_t key_sz);

void map_remove(Map *map, void *key, size_t key_sz);

void free_map(Map *map);

#endif /* map_h */
