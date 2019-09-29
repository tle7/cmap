////
//  test_map.c: this file test cmap.h functions
//
//  Created by Timothy Quang-Tin Le on 8/19/18.
//  Copyright © 2018 Timothy Quang-Tin Le. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "cmap.h"
#include <stdbool.h>

#define MAX_STR_LEN 24
#define NUM_STRS 8

void test_map_distrib_str() {
    printf("testing distribution of strings\n");
    char str_arr[NUM_STRS][MAX_STR_LEN] = {"ab", "ab2", "hi", "hola", "howdy", 
                                    "how are you doing today", "cmap", "hash"};
    Map *map = map_init();
    for (size_t i = 0; i < NUM_STRS; i++) {
        char *curr_str = str_arr[i];
        size_t curr_len = strlen(curr_str) + 1;
        map_put(map, curr_str, curr_str, curr_len, curr_len);
    }
    map_print_distrib(map);
    printf("\n");
    map_print_str_int_elems(map, true); 
    map_free(map);
    printf("\n");
}

void test_map_distrib_num() {
    printf("\ntest_map_distrib_num:\n");
    Map *map = map_init();
    size_t key_val_sz = sizeof(int);
    for (int ind = 0; ind < 2*MAP_NUM_BUCKETS; ind++) {
        map_put(map, &ind, &ind, key_val_sz, key_val_sz);
    }
    map_print_distrib(map);
    printf("\n");
    map_print_str_int_elems(map, false);
    map_free(map);
    printf("\n");
}

void test_add_two_nums() {
    Map *map = map_init();
    
    //add to map
    int key = 5;
    int val = 2;
    map_put(map, &key, &val, sizeof(key), sizeof(val));
    printf("added 1 elem, number of elems in map: %zu\n", 
            map_num_elems(map));
    
    //add second elem
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
    printf("\n");
}

void test_add_two_strs() {
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
    printf("\n");
}

int main(int argc, const char * argv[]) {
    test_add_two_nums();
    test_add_two_strs();

    test_map_distrib_str();
    return 0;
}
