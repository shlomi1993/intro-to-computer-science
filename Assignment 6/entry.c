#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "entry.h"

/***************************
* Name: Shlomi Ben Shushan *
* ID: *********            *
* Group: 01 - CS           *
* Assignment: 5			   *
***************************/

// This struct defines an entry in the dictionary.
struct Entry {
    int key;
    int value;
};

// This function alloacate memory to a new entry struct and initialize its fields.
Entry* create_entry(int key, int value) {
    Entry* entry = malloc(sizeof(Entry));
    if (entry != NULL) {
        entry->key = key;
        entry->value = value;
    }
    return entry;
}

// This function allocates memory to an entry without fill its fields.
void* allocate_entry() {
    return malloc(sizeof(Entry));
}

// Entry destructor.
void destroy_entry(void* p) {
    free(p);
}

// This function copies entry p2 to p1 (by pointer).
void copy_entry(void* p1, void* p2) {
    Entry* e1 = (Entry*) p1;
    Entry* e2 = (Entry*) p2;
    *e1 = *e2;
}

// Thisfunction compares two entries.
int compare_entry(void* p1, void* p2) {
    Entry* e1 = (Entry*) p1;
    Entry* e2 = (Entry*) p2;
    return e1->key - e2->key;
}

// This is a printer function.
void print_entry(void* p) {
    Entry* e = (Entry*) p;
    printf("[%d:%d]", e->key, e->value);
}

// A key getter.
int get_key(Entry* entry) {
    assert(entry != NULL);
    return entry->key;
}

// A value getter.
int get_value(Entry* entry) {
    assert(entry != NULL);
    return entry->value;
}

// A key setter.
void set_key(Entry* entry, int key) {
    assert(entry != NULL);
    entry->key = key;
}

// A value setter.
void set_value(Entry* entry, int value) {
    assert(entry != NULL);
    entry->value = value;
}
