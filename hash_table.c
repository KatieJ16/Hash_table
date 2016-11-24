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

    for(i = 0; i < strlen(s); i ++) {
        printf("s[%d] = %d", i, s[i]);
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
    node *(slots[NSLOTS]) = { NULL };
    hash_table *result = (hash_table *)malloc(sizeof(hash_table));
    
    if (result == NULL) {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->slot = slots;
    return result;

}


/* Free a hash table. */
void free_hash_table(hash_table *ht) {
    int i = 0;
    for(i = 0; i < NSLOTS; i ++) {
        free_list(ht->slot[i]);
    }
    free(ht->slot);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key) {
    int hash_num = hash(key);
    node *list = ht->slot[hash_num];
    
    /* when list is a blank list, definately no key. */
    if(list == NULL) {
        free_list(list);
        return 0;
    }


    /* in the right linked list, find the key and return the value */
    while(list->next != NULL) {    
        if(list->key == key) {
            free_list(list);
            return list->value;
        }
        list = list->next;
    }
    /* only happens when the key isn't in teh hash table. */
    free_list(list);
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value) {
    node *temp = NULL;
    int hash_num = hash(key);
    /* set list to the correct one based on the hash. */
    node *list = ht->slot[hash_num];

    /* whet key is already set to the correct value. */
    if(get_value(ht, key) == value) {
        return;
    }
    /* When key is already in hashtable, but a different value. */
    if(get_value(ht, key) != 0) {
        
        /* find key. */
        while(list != NULL) {
            /* Correct key, change value. */
            if(list->key == key) {
                list->value = value; 
            }
            list = list->next;
        }

    } else { /* when the value doesn't already exist, add a node. */
        /* make new node */
        temp = create_node(key, value);

        /* Then make the last current node point to the new node. */
        
        /* find end. */
        while(list->next != NULL) {
            list = list->next;
        }

        list->next = temp;

        /* make temp the end. */
        list = temp;
    }
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht) { 
    int i = 0;
    node *list;

    /* go through every linked list in the hash table. */
    for(i = 0; i < NSLOTS; i ++) {
        list = ht->slot[i];
        
        /* Go through very node in the linked list and print. */
        while(list->next != NULL) {
            printf("%s %d\n", list->key, list->value);
            list = list->next;
        }        
    }
}


