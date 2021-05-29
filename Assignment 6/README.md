# Assignment 6 - Dictionary based on Binary Tree with generics.

In this assignment we had to implement a dictionary using dynamic memory allocations. A dictionary is an abstract Data-Structure that map between keys and values. This implementation is based on Binary Tree data structure and its implemented generically, means the values can be any data-type.

## Dictionaty

the files dictionary.c and dictionary.h are the implementation of the dictionary data-structure with the following operations:
- initDictionary -- initialize a new dictionary, returns a pointer to it.
- destroyDictionary -- erase the dictionary and free all the memory allocated to it.
- sizeOfDictionary -- return the number of entries in the dictionary.
- putInDictionary -- add an entry to the dictionary.
- getFromDictionary -- get a dictionary value mapped to a given key.
- removeFromDictionary -- remove entry from the dictionary.
- printDictionary -- print the dictionary key-value entries.

## Entry

The files entry.c and entry.h are the implementation of the entry element in the dictionary.
Each entry contains a key, a value and there are some functions that one can use on entries.

## Binary Tree

As said, dictionary is an abstract data-structure, means it can be implemented with several concrete data-structure such as Binary Tree, AVL Tree or Linked List. This implementation is based on Binary Tree so the files BinTree.c and BinTree.h are the implementation for this Tree.

## Notes
- A major part of this assignment was to deal with the memory management and solve memory leaks.
- To detect memory leaks, I used Valgrind tool from https://valgrind.org/.
- The main.c file is only a driver/test code.


