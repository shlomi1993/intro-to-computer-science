#ifndef __ENTRY_H
#define __ENTRY_H

typedef struct Entry Entry;

Entry* create_entry(int key, int value);

int get_key(Entry* entry);
int get_value(Entry* entry);
void set_key(Entry* entry, int key);
void set_value(Entry* entry, int value);

void* allocate_entry();
void destroy_entry(void* p);
void copy_entry(void* p1, void* p2);
int compare_entry(void* p1, void* p2);
void print_entry(void* p);

#endif
