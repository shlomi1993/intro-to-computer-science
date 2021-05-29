#include <stdio.h>
#include "dictionary.h"

#include <stdlib.h>
#include <time.h>

#define BIG_SIZE 5000
#define MED_SIZE 1000
#define SMALL_SIZE 100

void showDictionary(Dictionary* dictionary) {
    printf("Size: %d\nDictionary: ", sizeOfDictionary(dictionary));
    printDictionary(dictionary);
    printf("\n");
}

void test1() {
    Dictionary* dictionary = initDictionary();
    showDictionary(dictionary);
    destroyDictionary(dictionary);
}

void test2() {
    Dictionary* dictionary = initDictionary();
    removeFromDictionary(dictionary, 1);
    destroyDictionary(dictionary);
}

void test3() {
    Dictionary* dictionary = initDictionary();
    putInDictionary(dictionary, 1, 8);
    putInDictionary(dictionary, 3, 6);
    putInDictionary(dictionary, 5, 4);
    putInDictionary(dictionary, 7, 2);
    showDictionary(dictionary);
    destroyDictionary(dictionary);
}

void test4() {
    Dictionary* dictionary = initDictionary();
    putInDictionary(dictionary, 5, 4);
    putInDictionary(dictionary, 7, 2);
    putInDictionary(dictionary, 3, 6);
    putInDictionary(dictionary, 1, 8);
    showDictionary(dictionary);
    destroyDictionary(dictionary);
}

void test5() {
    Dictionary* dictionary = initDictionary();
    putInDictionary(dictionary, 5, 4);
    putInDictionary(dictionary, 7, 2);
    putInDictionary(dictionary, 5, 6);
    putInDictionary(dictionary, 7, 8);
    showDictionary(dictionary);
    destroyDictionary(dictionary);
}

void test6() {
    Dictionary* d1 = initDictionary();
    putInDictionary(d1, 1, 8);
    putInDictionary(d1, 3, 6);
    putInDictionary(d1, 5, 4);
    putInDictionary(d1, 7, 2);

    int keys[] =   {1,3,5,7};
    int values[] = {8,6,4,2};
    int size = sizeof(keys) / sizeof(int);
    Dictionary* d2 = createDictionaryFromArrays(keys, values, size);

    for (int i = 0; i < size; i++) {
        int val1 = getFromDictionary(d1, keys[i]);
        int val2 = getFromDictionary(d2, keys[i]);

        if (val1 != val2) {
            printf("Error (vals)");
        }
    }
    destroyDictionary(d1);
    destroyDictionary(d2);
}

void test7() {
    srand(time(NULL));
    Dictionary* dictionary = initDictionary();
    int keys[BIG_SIZE] = {0};
    int values[BIG_SIZE] = {0};
    for (int i = 0; i < BIG_SIZE; i++) {
        keys[i] = i;
        values[i] = rand() % BIG_SIZE;
        putInDictionary(dictionary, keys[i], values[i]);
    }

    if (BIG_SIZE != sizeOfDictionary(dictionary)) {
        printf("Error (size) %d != %d\n", BIG_SIZE, sizeOfDictionary(dictionary));
    }

    for (int i = 0; i < BIG_SIZE; i++) {
        int val = getFromDictionary(dictionary ,keys[i]);
        if (val != values[i]) {
            printf("Error (val)\n");
        }
    }
    destroyDictionary(dictionary);
}

void test8() {
    srand(time(NULL));
    Dictionary* d1 = initDictionary();
    int keys[BIG_SIZE] =   {0};
    int values[BIG_SIZE] = {0};
    for (int i = 0; i < BIG_SIZE; i++) {
        keys[i] = i;
        values[i] = rand() % BIG_SIZE;
        putInDictionary(d1, keys[i], values[i]);
    }
    Dictionary* d2 = createDictionaryFromArrays(keys, values, BIG_SIZE);

    for (int i = 0; i < BIG_SIZE; i++) {
        int val1 = getFromDictionary(d1 ,keys[i]);
        int val2 = getFromDictionary(d2 ,keys[i]);
        if (val1 != val2) {
            printf("Error (val)\n");
        }
    }
    destroyDictionary(d1);
    destroyDictionary(d2);
}

void test9() {
    Dictionary* dictionary = initDictionary();
    putInDictionary(dictionary, 1, 8);
    putInDictionary(dictionary, 3, 6);
    putInDictionary(dictionary, 5, 4);
    putInDictionary(dictionary, 7, 2);
    removeFromDictionary(dictionary, 1);
    removeFromDictionary(dictionary, 2);
    removeFromDictionary(dictionary, 3);
    removeFromDictionary(dictionary, 4);
    showDictionary(dictionary);
    destroyDictionary(dictionary);
}

void test10() {
    srand(time(NULL));
    int keys[MED_SIZE] =   {0};
    int values[MED_SIZE] = {0};
    for (int i = 0; i < MED_SIZE; i++) {
        keys[i] = i;
        values[i] = rand() % MED_SIZE;
    }
    Dictionary* d1 = createDictionaryFromArrays(keys, values, MED_SIZE);
    Dictionary* d2 = createDictionaryFromArrays(keys, values, MED_SIZE - SMALL_SIZE);

    for (int i = MED_SIZE - SMALL_SIZE; i < MED_SIZE; i++) {
        removeFromDictionary(d1, keys[i]);
    }

    if (MED_SIZE - SMALL_SIZE != sizeOfDictionary(d1)) {
        printf("Error (size) %d %d\n", MED_SIZE - SMALL_SIZE, sizeOfDictionary(d1));
    }

    for (int i = 0; i < MED_SIZE - SMALL_SIZE; i++) {
        int val1 = getFromDictionary(d1 ,keys[i]);
        int val2 = getFromDictionary(d2 ,keys[i]);
        if (val1 != val2) {
            printf("Error (val)\n");
        }
    }

    destroyDictionary(d1);
    destroyDictionary(d2);
}

int main() {
    int input;
    scanf("%d", &input);
    if (input == 1) {
        test1();
    } else if (input == 2) {
        test2();
    } else if (input == 3) {
        test3();
    } else if (input == 4) {
        test4();
    } else if (input == 5) {
        test5();
    } else if (input == 6) {
        test6();
    } else if (input == 7) {
        test7();
    } else if (input == 8) {
        test8();
    } else if (input == 9) {
        test9();
    } else if (input == 10) {
        test10();
    }
}
