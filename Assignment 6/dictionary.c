#include <stdio.h>
#include <stdlib.h>

#include "entry.h"
#include "result.h"
#include "genericBinTree.h"

/***************************
* Name: Shlomi Ben Shushan *
* ID: *********            *
* Group: 01 - CS           *
* Assignment: 5			   *
***************************/

// This struct defines Dictionary as BinTree.
typedef struct {
    BinTree* tree;
} Dictionary;

// Define static fucntions.
static const BinTreeFunctions funcs = {
    allocate_entry,
    destroy_entry,
    copy_entry,
    compare_entry,
    print_entry
};

// This function initialize a new dictionary and allocate memory to it.
Dictionary* initDictionary() {
    Dictionary* d = malloc(sizeof(Dictionary));
    if (d == NULL) {
        return NULL;
    }
    d->tree = createBinTree(funcs);
    if (d->tree == NULL) {
        free(d);
        return NULL;
    }
    return d;
}

// This function destroy the dectionary by recursively free the allocated memory.
void destroyDictionary(Dictionary* d) {
    destroyBinTree(d->tree);
    free(d);
}

// This function add element to the dictionary.
Result putInDictionary(Dictionary* d, int key, int value) {
    Result result = SUCCESS;
    Entry* entry = create_entry(key, value);
    BinTree* root = findInBinTree(d->tree, entry);
    if (root) {
        Entry* copy = createCopyOfValueInRoot(root);
        removeFromBinTree(&d->tree, copy);
        destroy_entry(copy);
    }
    result = addToBinTree(d->tree, entry);
    destroy_entry(entry);
    return result;
}

// This function removes an element from the dictionary.
Result removeFromDictionary(Dictionary* d, int key) {
    Entry* entry = create_entry(key, 0);
    BinTree* root = findInBinTree(d->tree, entry);
    if (root == NULL) {
        destroy_entry(entry);
        return FAILURE;
    }
    Result result = removeFromBinTree(&d->tree, entry);
    destroy_entry(entry);
    return result;
}

// This function gives dictionary d a key and gets the value.
int getFromDictionary(Dictionary* d, int key) {
    Entry* entry = create_entry(key, 0);
    BinTree* root = findInBinTree(d->tree, entry);
    destroy_entry(entry);
    if (root == NULL) {
        return 0;
    }
    Entry* copy = createCopyOfValueInRoot(root);
    int returnVal = get_value(copy);
    destroy_entry(copy);
    return returnVal;
}

// This is a size getter.
int sizeOfDictionary(Dictionary* d) {
    return sizeOfBinTree(d->tree);
}

// This function is a printer.
void printDictionary(Dictionary* d) {
    printf("{");
    printInOrder(d->tree);
    printf("}");
}

// This function create a dictionary out of given arrays in a more efficient way than initialize and add element by element.
Dictionary* createDictionaryFromArrays(int keys[], int values[], int size) {
    Dictionary* dictionary = initDictionary(funcs);
    for (int i = 0; i < size; i++) {
        putInDictionary(dictionary, keys[i], values[i]);
    }
    return dictionary;
}
