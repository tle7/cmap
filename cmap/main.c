//
//  main.c
//  cmap
//
//  Created by Timothy Quang-Tin Le on 8/19/18.
//  Copyright © 2018 Timothy Quang-Tin Le. All rights reserved.
//

#include <stdio.h>
#include "map.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    Map *map = init_map();
    
    //add to map
    int key = 5;
    int val = 2;
    map_put(map, &key, &val, sizeof(key), sizeof(val));
    map_elem *first_elem = map->elem_arr[0];
    printf("first key is %d with val %d\n", *((int *) first_elem->key),
           *((int *) first_elem->val));
    
//    add second elem
    map_put (map, &val, &key, sizeof(val), sizeof(key));
    map_elem *second_elem = first_elem->next;
    if (!second_elem)
        printf("no second elem found");
    else
        printf ("second key is %d with val %d\n", *((int*) second_elem->key),
                *((int*) second_elem->val));
    
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
        printf("new first elem has key: %d and val: %d\n", *((int*) new_first_elem->key),
               *((int*) new_first_elem->val));
    
    //make sure getting new first elem is successful
    const void *retrv_val = map_get(map, &val, sizeof(val));
    if (retrv_val)
        printf("retrv val with key %d has val: %d\n", val,
               *((int*) retrv_val));
    
    //remove second item
    map_remove(map, &val, sizeof(val));
    const void *retrv_null = map_get(map, &val, sizeof(val));
    if (!retrv_null)
        printf("successfully removed second elem\n");
    
    free_map(map);
    
    return 0;
}
