#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "stack.h"
#include "queue.h"
#include "strings.h"

/***************************
* Name: Shlomi Ben Shushan *
* ID: *********            *
* Group: 01 - CS           *
* Assignment: 5 (file 1/3) *
***************************/

/**************************************************************************************************
* Function name:        initStack
* Input:                None.
* Output:               Pointer to stack address in the memory.
* Function Operation:   This function initialize a stack. It allocates memory for a struct that
                        include the content and two ints for size and top-index.
                        If allocation success, the function will return a pointer as described.
                        If allocation fails, it will return an error massage and Null value.
**************************************************************************************************/
Stack* initStack() {

    Stack* stack = malloc(sizeof(stack));
    stack->content = malloc(sizeof(Element));
    stack->size = 1;
    stack->topIndex = -1;
    if ( stack == NULL || stack->content == NULL ) {
        printf("Stack: initStack: Heap memory error!");
        return NULL;
    } else {
        return stack;
    }

}

/**************************************************************************************************
* Function name:        destroyStack
* Input:                Pointer to stack.
* Output:               None.
* Function Operation:   This function uses the function free() to clear the memory allocated for
                        the content of the stack and afterwards it clears the memory allocated for
                        for the stack itself.
**************************************************************************************************/
void destroyStack(Stack* stack) {

    if ( stack->content != NULL ) {
        free(stack->content);
    }
    if ( stack != NULL ) {
        free(stack);
    }

}

/**************************************************************************************************
* Function name:        isStackEmpty
* Input:                Pointer to stack.
* Output:               1 - Empty, 0 - Not.
* Function Operation:   This function check if stacks top index is -1. If so, it means that the
                        stack is empty so return 1. If now, it means that there is at least one
                        member in the stack so return 0 (not empty).
**************************************************************************************************/
int isStackEmpty(Stack* stack) {

    if ( stack->topIndex == -1 ) {
        return 1;
    } else {
        return 0;
    }

}

/**************************************************************************************************
* Function name:        lenOfStack
* Input:                Pointer to stack.
* Output:               int len - a number that represent the number of members in stack's content.
* Function Operation:   This function checks top-index and add 1. This way it can tell how many
                        members in the stack (in it's content).
**************************************************************************************************/
int lenOfStack(Stack* stack) {

    int len = stack->topIndex+1;
    return len;

}

/**************************************************************************************************
* Function name:        capacityOfStack
* Input:                Pointer to stack.
* Output:               int cap - represent the number of bytes used by stack's members.
* Function Operation:   This function check the size of each element in the stack so it can sum
                        all the sizes to a total capacity of the stack. The loop designed to
                        support all kind of element sizes (char, int, double, long, etc...).
**************************************************************************************************/
int capacityOfStack(Stack* stack) {

    int cap = 0;
    for ( int i = 0 ; i < lenOfStack(stack) ; i++ ) {
        cap += sizeof(stack->content[i]);
    }
    return cap;

}

/**************************************************************************************************
* Function name:        push
* Input:                Pointer to stack and given element.
* Output:               None.
* Function Operation:   First, this function check if the memory allocated for the stack is enough
                        for it's current capacity plus another element. If so, it will add it to
                        the stack's content and advance the top-index by 1. If not, which means
                        that size is lower or equal to current capacity + new element (according
                        to instructions), it will double size (until it will be higher than
                        capacity+element) and use realloc() function to find suitable space in
                        the memory.
**************************************************************************************************/
void push(Stack* stack, Element element) {

    if ( stack->size > sizeof(element)+capacityOfStack(stack) ) {
        stack->content[stack->topIndex+1] = element;
        stack->topIndex++;
    } else {
        while ( stack->size <= sizeof(element)+capacityOfStack(stack) ) {
            stack->size *= 2;
        }
        Stack* newAddress = realloc(stack->content, stack->size);
        if ( newAddress != NULL ) {
            stack->content = newAddress;
        }
        stack->content[stack->topIndex+1] = element;
        stack->topIndex++;
    }

}

/**************************************************************************************************
* Function name:        pop
* Input:                Pointer to stack.
* Output:               The popped element.
* Function Operation:   This function reduce size if possible (divide it by 2) and if success, use
                        realloc() to find a better address to allocate stack's content.
                        In addition, it reduce the top-index by 1 (because the upper  member had
                        popped from the stack) and return the popped element.
**************************************************************************************************/
Element pop(Stack* stack) {

    if ( stack->size <= 2*capacityOfStack(stack) ) {
        stack->topIndex--;
        return stack->content[stack->topIndex+1];
    } else {
        while ( stack->size > 2*capacityOfStack(stack) ) {
            stack->size /= 2;
        }
        Stack* newAddress = realloc(stack->content, stack->size);
        if ( newAddress != NULL ) {
            stack->content = newAddress;
        }
        stack->topIndex--;
        return stack->content[stack->topIndex+1];
    }

}

/**************************************************************************************************
* Function name:        top
* Input:                Pointer to stack.
* Output:               The element in the top of the stack.
* Function Operation:   This function simply return the top-indexed member in the stack.
**************************************************************************************************/
Element top(Stack* stack) {

    return stack->content[stack->topIndex];

}

/**************************************************************************************************
* Function name:        printStack
* Input:                Pointer to stack.
* Output:               A list that describe the stack.
* Function Operation:   Prints stack's content.
**************************************************************************************************/
void printStack(Stack* stack) {

    for ( int i = 1+stack->topIndex ; i > 0 ; i-- ) {
        printf("%d: ", i);
        printElement(stack->content[i-1]);
        printf("\n");
    }

}

