//
//  map.c
//  cmap
//
//  Created by Timothy Quang-Tin Le on 8/19/18.
//  Copyright © 2018 Timothy Quang-Tin Le. All rights reserved.
//

#include "map.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

//private helpers
//will add hash function
static int get_bucket_num(void *key, size_t key_len) {
    assert (key && key_len > 0);
    
    return 0;
}

static void map_add_elem(Map *map, map_elem *add_elem) {
    assert (map && add_elem);
    int bucket_num = get_bucket_num(add_elem->key, add_elem->key_sz);
    map_elem *list_node = map->elem_arr[bucket_num];
    
    //add elem
    if (!list_node) {
        map->elem_arr[bucket_num] = add_elem;
        return;
    }
    
    while (list_node->next)
        list_node = list_node->next;
    list_node->next = add_elem;
    add_elem->prev = list_node;
}

//get and delete use this helper to retrieve the queried elem
static map_elem *get_map_elem(Map *map, void *key, size_t key_sz) {
    int bucket_num = get_bucket_num(key, key_sz);
    map_elem *search_elem = map->elem_arr[bucket_num];
    
    while (search_elem) {
        if (key_sz == search_elem->key_sz &&
            memcmp(key, search_elem->key, key_sz) == 0) {
            return search_elem;
        }
        search_elem = search_elem->next;
    }
    return NULL;
}

//public functions
Map *init_map() {
    Map *new_map = malloc(sizeof(Map));
    
    for (size_t i = 0; i < MAP_ARRAY_SZ; i++)
        new_map->elem_arr[i] = NULL;
    return new_map;
}

void map_put(Map *map, void *key, void *val, size_t key_sz, size_t val_sz) {
    assert (map && key && val && key_sz > 0 && val_sz > 0);
    
    
    map_elem *new_map_elem = malloc(sizeof(map_elem));
    if (!new_map_elem)
        return;
    
    //init key fields
    new_map_elem->key = malloc(key_sz);
    memcpy(new_map_elem->key, key, key_sz);
    new_map_elem->key_sz = key_sz;
    
    //init val fields
    void *copy_val = malloc(val_sz);
    memcpy(copy_val, val, val_sz);
    new_map_elem->val = copy_val;
    new_map_elem->val_sz = val_sz;
    
    //add map_elem to map
    new_map_elem->next = NULL;
    new_map_elem->prev = NULL;
    map_add_elem(map, new_map_elem);
}

/* returns a pointer to the val
 * returns NULL if no value exists
 */
const void *map_get(Map *map, void *key, size_t key_sz) {
    
    map_elem *found_elem = get_map_elem(map, key, key_sz);
    if (!found_elem)
        return NULL;
    return found_elem->val;
}

void map_remove(Map *map, void *key, size_t key_sz) {
    map_elem *remove_elem = get_map_elem(map, key, key_sz);
    if (!remove_elem)
        return;

    //free elem pointers
    free(remove_elem->key);
    free(remove_elem->val);

    //connect elem's prev and next
    if (remove_elem->prev)
        remove_elem->prev->next = remove_elem->next;
    else {
        //removed elem is head of list
        int bucket_num = get_bucket_num(key, key_sz);
        map->elem_arr[bucket_num] = remove_elem->next;
    }
    if (remove_elem->next)
        remove_elem->next->prev = remove_elem->prev;

    free(remove_elem);
}

void free_map(Map *map) {
    //free all elements in map
    for (size_t i = 0; i < MAP_ARRAY_SZ; i++) {
        //free all items in each bucket
        map_elem *curr_elem = map->elem_arr[i];
        map_elem *next_elem = NULL;
        while (curr_elem) {
            printf("freeing elem in free_map\n");
            next_elem = curr_elem->next;
            free(curr_elem->key);
            free(curr_elem->val);
            free(curr_elem);
            
            curr_elem = next_elem;
        }
    }
    
    free(map);
}