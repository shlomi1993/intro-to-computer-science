#include <stdio.h>
#include <math.h>

/***************************
* Name: Shlomi Ben Shushan *
* ID: *********            *
* Group: 01 - CS           *
* Assignment: 3            *
***************************/

// Set global counter
int counter = 0;

// Calculating power by iterative definition
double iterPow(double x, int y) {
    // Case zero power
    double res = 1;
    if ( y == 0) {
        res = 1;
        counter++;
    }
    // Case positive power
    else if ( y > 0 ) {
        for ( int i = y ; i > 0 ; i-- ) {
        res *= x;
        counter++;
        }
    }
    // Case negative power
    else {
        for ( int i = -y ; i > 0 ; i-- ) {
        res *= 1/x;
        counter++;
        }
    }
    return res;
}

// Calculating power by naive recursion
double recPow(double x, int y) {

    counter++;
    // Split to different cases
    if ( y == 0 ) {
        return 1;
    } else if ( y == 1 ) {
        return x;
    } else if ( y == -1 ) {
        return 1/x;
    } else if ( y > 1 ) {
        return x*recPow(x, --y);
    } else if ( y < -1 ) {
        int temp = -y;
        return 1/(x*recPow(x, --temp));
    } else {
        return 1;
    }

}

// Calculating power by efficient recursion
double recEffiPow(double x, int y) {

    counter++;
    // Split to different cases
    if ( y == 0 ) {
        return 1;
    } else if ( y == 1 ) {
        return x;
    } else if ( y == -1 ) {
        return 1/x;
    } else if ( y > 1 ) {
        // Define recursion effectively - for case positive power
        double effiPow = recEffiPow(x, y/2);
        if ( y%2 == 0 ) {
            return effiPow*effiPow;
        } else {
            return x*effiPow*effiPow;
        }
    } else if ( y < -1 ) {
        // Define recursion effectively - for case negative power
        double effiPow = recEffiPow(x, (-y)/2);
        if ( y%2 == 0 ) {
            return 1/(effiPow*effiPow);
        } else {
            return 1/(x*effiPow*effiPow);
        }
    } else {
        return 1;
    }


}

// Finding a permutation
int isPermutation(int arr1[], int size1, int arr2[], int size2) {

    int temp = 0, num = 0;
    // Size comparison
    if ( size1 != size2 ) {
        return 0;
    }
    // Values comparison
    else {
        // Cloning arrays
        int arr1Copy[size1], arr2Copy[size2];
        for ( int i = 0 ; i < size1 ; ++i ) {
            arr1Copy[i] = arr1[i];
            arr2Copy[i] = arr2[i];
        }
        // Sort array 1 copy
        for ( int i = 0 ; i < size1-1 ; ++i ) {
            for ( int j = 0 ; j < size1-1-i ; ++j ) {
                if ( arr1Copy[j] > arr1Copy[j+1] ) {
                    temp = arr1Copy[j+1];
                    arr1Copy[j+1] = arr1Copy[j];
                    arr1Copy[j] = temp;
                }
            }
        }
        // Sort array 2 copy
        for ( int i = 0 ; i < size2-1 ; ++i ) {
            for ( int j = 0 ; j < size2-1-i ; ++j ) {
                if ( arr2Copy[j] > arr2Copy[j+1] ) {
                    temp = arr2Copy[j+1];
                    arr2Copy[j+1] = arr2Copy[j];
                    arr2Copy[j] = temp;
                }
            }
        }
        // Arrays comparison
        while ( num < size1 ) {
            if ( arr1Copy[num] != arr2Copy[num] ) {
                return 0;
            }
            num++;
        }
        return 1;
    }

}

// Convert a 2D array to an aligned table
void printArr2D(int arr[][MAX], int rows, int columns) {
    // Variables declaration
    int longNum = 0, lenLong = 0, len = 0, zeros = 0;
    // Look for the longest number in the array
    for ( int i = 0 ; i < rows ; i++ ) {
        for ( int j = 0 ; j < columns ; j++ ) {
            if ( arr[i][j] > longNum ) {
                longNum = arr[i][j];
            }
        }
    }
    // Use log10 function to find length (with instructor's permission)
    lenLong = log10(longNum)+1;
    // Print table
    for ( int i = 0 ; i < rows ; i++ ) {
        for ( int j = 0 ; j < columns ; j++ ) {
            // Case print zero
            if ( arr[i][j] == 0 ){
                for ( int k = lenLong ; k > 1 ; k-- ) {
                    printf("0");
                }
            // Case print number > zero (no negative number according to instructions)
            } else {
                // Determine how many zeros to print before the number
                len = log10(arr[i][j])+1;
                zeros = lenLong-len;
                // Print zeros
                for ( int k = zeros ; k > 0 ; k-- ) {
                    printf("0");
                }
                len = 0;
            }
            // Print the relevant number
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

}

