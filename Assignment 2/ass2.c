#include <stdio.h>
#include <stdlib.h>

/***************************
* Name: Shlomi Ben Shushan *
* ID: *********            *
* Group: 01 - CS           *
* Assignment: 2            *
***************************/

void draw() {
    // Variables declaration
    int num, edge, i;
        // Ask for input
        printf("Enter a number: ");
        scanf("%d", &num);
        // Calculating edge length without corners
        edge = 2*num-1;
        // Extreme case
        if ( num == 0 ) {
            printf("X\n");
        }
        // Regular case
        else if ( num > 0 ) {
            // Handling top raw
            printf("+");
            for ( i = edge ; i > 0 ; i-- ) {
                printf("-");
            }
            printf("+\n");
            // Handling middle raws above X line
            int raw = 0;
            while ( raw < (edge/2) ) {
                printf("|");
                for ( i = raw ; i > 0 ; i-- ) {
                    printf(" ");
                }
                printf("\\");
                for ( i = ((edge/2)-raw) ; i > 1 ; i-- ) {
                    printf(" ");
                }
                printf(" ");
                for ( i = ((edge/2)-raw) ; i > 1 ; i-- ) {
                    printf(" ");
                }
                printf("/");
                for ( i = raw ; i > 0 ; i-- ) {
                    printf(" ");
                }
                printf("|\n");
                raw++;
                }
            // Handling X line
            printf("|");
            for ( i = (edge/2) ; i > 0 ; i-- ) {
                printf(" ");
            }
            printf("X");
            for ( i = (edge/2) ; i > 0 ; i-- ){
                printf(" ");
            }
            printf("|\n");
            // Handling middle raws below X line
            raw = (edge/2);
            while ( raw > 0 ) {
                printf("|");
                for ( i = raw ; i > 1 ; i-- ) {
                    printf(" ");
                }
                printf("/");
                for ( i = ((edge/2)-raw) ; i > 0 ; i-- ) {
                    printf(" ");
                }
                printf(" ");
                for ( i = ((edge/2)-raw) ; i > 0 ; i-- ) {
                    printf(" ");
                }
                printf("\\");
                for ( i = raw ; i > 1 ; i-- ) {
                    printf(" ");
                }
                printf("|\n");
                raw--;
            }
            // Handling bottom raw
            printf("+");
            for ( i = edge ; i > 0 ; i-- ) {
                printf("-");
            }
            printf("+\n");
        }
        else {
            printf("Error: number cannot be negative.");
        }

}

void isEvenLength() {
    // Variables declaration
    char str;
    int len = -1;
    // Ask for input
    printf("Enter text: ");
    // Scanning and measuring method
    scanf("% c", &str);
    while ( str != '\n' ) {
        len++;
        scanf("%c", &str);
    }
    // Decide ODD or EVEN and print
    if ( len&1 ) {
        printf("Your text's length is odd\n");
    } else {
        printf("Your text's length is even\n");
    }

}

void identifyText() {
    // Variables declaration
    char current, next;
    int temp, itr = -1, isNotValid = 0, isAsc = 0, isDec = 0, isCon = 0;
    // Ask for input and scanning method
    printf("Enter text: ");
    scanf(" %c", &next);
    while ( next != '\n' ) {
        if ( next >= 'a' && next <= 'z' ) {
            if ( itr > -1 ) {
                temp = next-current;
                if ( temp > 0 ) {
                    isAsc += 1;
                } else if ( temp < 0 ) {
                    isDec += 1;
                } else {
                    isCon += 1;
                }
            }
        } else {
            isNotValid = 1;
        }
        itr++;
        current = next;
        scanf("%c", &next);
    }
    // Case decision and print result
    if ( isAsc == 0 && isDec == 0 && isCon == itr && isNotValid == 0 ) {
        printf("your text is constant\n");
    } else if ( isAsc+isCon == itr && isDec == 0 && isNotValid == 0 ) {
        printf("your text is increasing\n");
    } else if ( isAsc == 0 && isDec+isCon == itr && isNotValid == 0 ) {
        printf("your text is decreasing\n");
    } else if ( isNotValid ) {
        printf("your text is invalid\n");
    } else {
        printf("your text is mixed\n");
    }

}

void hexToDec() {
    // Variables declaration
    char hex;
    int power, loc = 0, stop = 0;
    long dec = 0;
    // Ask user for input
    printf("Enter a reversed number in base 16: ");
    // Scanning and converting to decimal
    scanf(" %c", &hex);
    while ( hex != '\n' ) {
        if ( hex >= '0' && hex <= '9' ) {
            hex -= '0';
        } else if ( hex >= 'a' && hex <= 'f' ) {
            hex -= 'W';
        } else if ( hex >= 'A' && hex <= 'F' ) {
            hex -= '7';
        } else {
            printf("Error! %c is not a valid digit in base 16\n", hex);
            stop = 1;
        }
        // Calculating base*power
        power = loc;
        if ( power == 0 ) {
            dec += hex;
        // And if power > 0 (power cannot be negative)
        } else {
            int expo = 1;
            for ( int i = power ; i > 0 ; i-- ) {
                expo *= 16;
            }
            dec += hex*expo;
        }
        loc++;
        scanf("%c", &hex);
    }
    // Prints only if all inputs are legit
    if (stop != 1) {
        printf("%ld\n", dec);
    }

}

void baseToDec() {
    // Variables declaration
    char raw;
    int base, num, power, loc = 0, expo, stop = 0;
    long dec = 0;
    // Ask user for base and scan
    printf("Enter a base (2-10): ");
    scanf(" %d", &base);
    // Ask user for a reversed number and scan first non-whitespace char
    printf("Enter a reversed number in base %d: ", base);
    scanf(" %c", &raw);
    // Scanning and calculating method
    while ( raw != '\n' ) {
        num = raw-'0';
        if ( num >= 0 && num < base ) {
            power = loc;
            // Case 0
            if ( power == 0 ) {
                dec += num;
            // Case power > 0 (minus is not a legit input)
            } else {
                // Handling exponent
                expo = 1;
                for ( int i = power ; i > 0 ; i-- ) {
                    expo *= base;
                }
                dec += num*expo;
            }
            loc++;
        } else {
            stop = 1;
            printf("Error! %c is not a valid digit in base %d\n", raw, base);
        }
        scanf("%c", &raw);
    }
    // Prints result if all digits are valid
    if ( stop == 0 ) {
        printf("%ld\n", dec);
    }

}

void bitCount() {
    // Variables declaration
    int dec, temp, bits = 0;
    // Ask the user and scan
    printf("Enter a number: ");
    scanf("%d", &dec);
    // For positive or zero:
    if ( dec >= 0 ){
        temp = dec;
        while ( temp > 0 ) {
            if ( temp%2 == 1 ) {
                bits += 1;
            }
            temp /= 2;
        }
    // For negative:
    } else {
        // Assume 32 bit environment
        bits += 32;
        temp = ~dec;
        while ( temp > 0 ) {
            if ( temp%2 == 1 ) {
                bits -= 1;
            }
            temp /= 2;
        }
    }
    // Printing wanted number of bits
    printf("The bit count of %d is %d\n", dec, bits);

}

void main() {
    int choice;
    do {
        printf("Choose an option:\n1: Draw\n2: Even or Odd\n3: Text type\
                \n4: Hex to Dec\n5: Base to Dec\n6: Count bits\n0: Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: draw();
                    break;
            case 2: isEvenLength();
                    break;
            case 3: identifyText();
                    break;
            case 4: hexToDec();
                    break;
            case 5: baseToDec();
                    break;
            case 6: bitCount();
            case 0: break;
            default: printf("Wrong option!\n");
        }
    } while (choice != 0);
}
