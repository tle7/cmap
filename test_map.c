////
//  main.c
//  cmap
//
//  Created by Timothy Quang-Tin Le on 8/19/18.
//  Copyright © 2018 Timothy Quang-Tin Le. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "cmap.h"


int main(int argc, const char * argv[]) {
    Map *map = map_init();
    
    //add to map
    int key = 5;
    int val = 2;
    map_put(map, &key, &val, sizeof(key), sizeof(val));
    printf("added 1 elem, number of elems in map: %zu\n", 
            map_num_elems(map));
    
//    add second elem
    int second_key = 555;
    int second_val = 45;
    map_put (map, &second_key, &second_val, sizeof(second_val), 
            sizeof(second_key));
    
    //test get function
    const void *first_val = map_get(map, &key, sizeof(key));
    if (!first_val)
        printf("getting first val unsuccessful\n");
    else
        printf("used \'get\' and retrieved val: %d\n", *((int*) first_val));
    
    //test remove
    map_remove(map, &key, sizeof(key));
    
    const void *remove_val = map_get(map, &key, sizeof(key));
    if (!remove_val)
        printf("elem was sucessfully removed\n");
    
    map_elem *new_first_elem = map->elem_arr[0];
    if (new_first_elem)
        printf("new first elem has key: %d and val: %d\n", 
                *((int*) new_first_elem->key),
               *((int*) new_first_elem->val));
    
    //make sure getting new first elem is successful
    const void *retrv_val = map_get(map, &val, sizeof(val));
    if (retrv_val)
        printf("retrv val with key %d has val: %d\n", val,
               *((int*) retrv_val));
    
    //remove second int item
    map_remove(map, &second_key, sizeof(val));
    const void *retrv_null = map_get(map, &second_key, sizeof(val));
    if (!retrv_null)
        printf("successfully removed second elem\n");
    
    map_free(map);
    
    Map *second_map = map_init();
    char *str_key = "hola";
    char *str_val = "hi";
    size_t key_len = strlen(str_key) + 1;
    size_t val_len = strlen(str_val) + 1;
    map_put(second_map, str_key, str_val, key_len, val_len);
    
    const char *retrv_str1 = map_get(second_map, str_key, key_len);
    printf("key: %s, val: %s\n", str_key, retrv_str1);
    
    char *str_key2 = "how are you?";
    char *str_val2 = "como estas?";
    size_t key_len2 = strlen(str_key2) + 1;
    size_t val_len2 = strlen(str_val2) + 1;
    map_put(second_map, str_key2, str_val2, key_len2, val_len2);
    
    const char *retrv_str2 = map_get(second_map, str_key2, key_len2);
    printf("key %s, val: %s\n", str_key2, retrv_str2);
    
    map_free(second_map);
    
    return 0;
}
