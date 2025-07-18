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
* Assignment: 5 (file 3/3) *
***************************/

/**************************************************************************************************
* Function name:        isLegalString
* Input:                given string (char array).
* Output:               1 - Legal, 0 - Not.
* Function Operation:   Phase 1 - uses initStack() function to initialize a stack named s3.
                        Phase 2 - scan given string for parenthesis openers and push them to s3.
                        Phase 3 - convert between elements and char as needed.
                        Phase 4 - using top() function to compare given char to the top of s3 stack.
                        (Phses 2-4 in the same loop)
                        Phase 5 - use isStackEmpty() to determine if s3 is empty or not.
                            if so, destroy stack (clear memory) and return 1.
                            if not, destroy stack (clear memory) and return 0.
                        Note: if the stack is empty it means that the function found a parenthesis
                        bracket for each parenthesis opener.
**************************************************************************************************/
int isLegalString(char str[]) {

    Stack* s3 = initStack();
    Element element;
    char convertTop;

    for ( int i = 0 ; i < strlen(str) ; i++ ) {
        element.c = str[i];
        if ( str[i] == '(' || str[i] == '[' || str[i] == '{' || str[i] == '<' ) {
            push(s3, element);
        }
        Element e = top(s3);
        convertTop = e.c;
        if ( element.c == ')' && convertTop == '(' ) {
            pop(s3);
        } else if ( element.c == ']' && convertTop == '[' ) {
            pop(s3);
        } else if ( element.c == '}' && convertTop == '{' ) {
            pop(s3);
        } else if ( element.c == '>' && convertTop == '<' ) {
            pop(s3);
        }
    }
    if ( isStackEmpty(s3) ) {
        destroyStack(s3);
        return 1;
    } else {
        destroyStack(s3);
        return 0;
    }
}
