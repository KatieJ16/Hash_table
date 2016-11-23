/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s) {
    int sum = 0;
    int i = 0;

    for(i = 0; i < sizeof s; i ++) {
        sum = sum + s[i];
    }

    return sum % NSLOTS;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value) {
    node *result = (node *)malloc(sizeof(node));

    if (result == NULL) {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->key = key;
    result->value = value;
    result->next = NULL;

    return result;

}


/* Free all the nodes of a linked list. */
void free_list(node *list) {
    node *n;     /* a single node of the list */

    while (list != NULL) {
        n = list;
        list = list->next;
        free(n);
    }

}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table() {
    hash_table *result = (hash_table *)malloc(sizeof(hash_table));
    node *slotstart  = (node *) malloc(sizeof(node));
    if (result == NULL || slotstart == NULL) {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->slot = &(slotstart);
    return result;

}


/* Free a hash table. */
void free_hash_table(hash_table *ht){
    node *list = *(ht->slot); 
    node *n;
    while (list != NULL) {
        n = list;
        list = list->next;
        free_list(n);
        /*
         * 'n' now points to the first element of the list, while
         * 'list' now points to everything but the first element.
         * Since nothing points to 'n', it can be freed.
         */
        
        /*free(n);*/
    }
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key) {
    int value = hash(key);
    node *key_list = NULL;
    /* set list to the first node of the slot array. */
    node *list = *(ht->slot);
    
    /* check every node of the array of arrays. */
    while(list != NULL) {
        key_list = list->value;
        list = list->next;
            
        /* when correct value, make sure key is in it. */
        if(key_list->value == value) {
            while(key_list != NULL) {
                if(key_list->key == key) {
                    return value;
                }
                key_list = key_list->next;
            }
            return 0;
        }
    }

    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value){
    node *key_list = NULL;
    node *temp = NULL;
    /* set list to the first node of the slot array. */
    node *list = *(ht->slot);
            
    /* When key is already in hashtable. */
    if(get_value != 0) {
        
        /* check every node of the array of arrays. */
        while(list != NULL) {
            key_list = list->value;
            list = list->next;
                                            
            /* when correct value, add a key to the end of the list. */
            if(key_list->value == value) {
                /* find the last link. */
                while(key_list != NULL) {
                    key_list = key_list->next;
                }
            
                /* add new node to the end */
                temp = create_node(key, value);
            
                /* make the last node point to the new node */
                key_list->next = temp;

                /* make temp the new end. */
                key_list = temp;
            }
        }

    } else { /* when the value doesn't already exist, add a node. */


    }
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{

}


