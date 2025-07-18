#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "stack.h"
#include "queue.h"
#include "strings.h"

/***************************
* Name: Shlomi Ben Shushan *
* Group: 01 - CS           *
* Assignment: 5 (file 2/3) *
***************************/

/**************************************************************************************************
* Function name:        initQueue
* Input:                None.
* Output:               Pointer to queue's address in the memory.
* Function Operation:   This function initialize the queue. It uses malloc to find available space
                        in the memory for the queue and uses the function initStack() to
                        initialize two stacks: s1, s2. The function will return Null if malloc
                        fails and return pointer to queue if success.
**************************************************************************************************/
Queue* initQueue() {

    Queue* queue = malloc(sizeof(queue));
    queue->s1 = initStack();
    queue->s2 = initStack();

    if ( queue == NULL ) {
        printf("Stack: initQueue: Heap memory error!");
        return NULL;
    } else {
        return queue;
    }

}

/**************************************************************************************************
* Function name:        destroyQueue
* Input:                Pointer to Queue.
* Output:               None.
* Function Operation:   This function uses destroyStack() function to neatly free memory allocated
                        to s1 and s2 stacks and afterwards it uses free() function to free memory
                        allocated to the queue itself.
**************************************************************************************************/
void destroyQueue(Queue* queue) {

    destroyStack(queue->s1);
    destroyStack(queue->s2);
    free(queue);

}

/**************************************************************************************************
* Function name:        isQueueEmpty
* Input:                Pointer to Queue.
* Output:               1 - Queue is empty. 0 - It is not.
* Function Operation:   This function uses isStackEmpty() function to to check if both of the
                        stacks in the queue (s1, s2) are empty. If so, return 1. If not, return 0.
**************************************************************************************************/
int isQueueEmpty(Queue* queue) {

    if ( isStackEmpty(queue->s1) == 1 && isStackEmpty(queue->s2) == 1 ) {
        return 1;
    } else {
        return 0;
    }

}

/**************************************************************************************************
* Function name:        lenOfQueue
* Input:                Pointer to Queue.
* Output:               int totalLen = amount of members in the queue.
* Function Operation:   This function uses lenOfStack() function to count members in both of the
                        stacks in the queue (s1 and s2).
**************************************************************************************************/
int lenOfQueue(Queue* queue) {

    int len1, len2, totalLen;

    len1 = lenOfStack(queue->s1);
    len2 = lenOfStack(queue->s2);
    totalLen = len1+len2;

    return totalLen;

}

/**************************************************************************************************
* Function name:        capacityOfQueue
* Input:                Pointer to Queue.
* Output:               int totalCap = amount of bytes used by queue.
* Function Operation:   This function uses capacityOfStack() to count bytes used by s1 and s2 and
                        sum it to totalCap = total capacity of queue's content.
**************************************************************************************************/
int capacityOfQueue(Queue* queue) {

    int cap1, cap2, totalCap;

    cap1 = capacityOfStack(queue->s1);
    cap2 = capacityOfStack(queue->s2);
    totalCap = cap1+cap2;

    return totalCap;

}

/**************************************************************************************************
* Function name:        enqueue
* Input:                Pointer to Queue and given element.
* Output:               None.
* Function Operation:   This function uses push() function to add given element to s1 stack.
**************************************************************************************************/
void enqueue(Queue* queue, Element element) {

    push(queue->s1, element);

}

/**************************************************************************************************
* Function name:        dequeue
* Input:                Pointer to Queue.
* Output:               int temp = the popped element.
* Function Operation:   First, this function transfer all the elements enqueued to s1, to s2.
                        Second, it pop to element in the top s2 stack (which was the top of the
                        queue when it was in s1).
                        Afterwards, it transfer all the elements back to s2 (in order to be able
                        to use enqueue only on s1).
                        Finally, the function returns the value of the popped element.
**************************************************************************************************/
Element dequeue(Queue* queue) {

    for ( int i = 0 ; i < lenOfQueue(queue) ; i++ ) {
        push(queue->s2, pop(queue->s1));
    }
    Element temp = pop(queue->s2);
    for ( int i = 0 ; i < lenOfQueue(queue) ; i++ ) {
        push(queue->s1, pop(queue->s2));
    }
    return temp;

}

/**************************************************************************************************
* Function name:        peek
* Input:                Pointer to Queue.
* Output:               The element in the top of the queue.
* Function Operation:   Simply return content[0] of s1 stack.
**************************************************************************************************/
Element peek(Queue* queue) {

    Element firstInQueue = queue->s1->content[0];
    return firstInQueue;

}

