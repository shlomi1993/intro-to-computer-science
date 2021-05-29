#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "ass4.h"

/***************************
* Name: Shlomi Ben Shushan *
* ID: *********            *
* Group: 01 - CS           *
* Assignment: 4            *
***************************/

// Move logical representation
typedef struct {
    char srcPiece, srcRow, srcCol, destPiece, destRow, destCol, boardCopy[SIZE][SIZE], pathBoard[SIZE][SIZE];
    int iSrc, jSrc, iDest, jDest;
    int isWhite, isCapture, isPromotion, isCheck, isMate, isLegal;
} Move;

// PGN characters
const char PAWN = 'P';
const char ROOK = 'R';
const char KNIGHT = 'N';
const char BISHOP = 'B';
const char QUEEN = 'Q';
const char KING = 'K';
const char CAPTURE = 'x';
const char PROMOTION = '=';
const char CHECK = '+';
const char MATE = '#';
const char FIRST_COL = 'a';

// FEN & Board characters
const int IS_EMPTY = 0;
const int IS_WHITE = 1;
const int IS_BLACK = 2;
const char WHITE_PAWN = 'P';
const char WHITE_ROOK = 'R';
const char WHITE_KNIGHT = 'N';
const char WHITE_BISHOP = 'B';
const char WHITE_QUEEN = 'Q';
const char WHITE_KING = 'K';
const char BLACK_PAWN = 'p';
const char BLACK_ROOK = 'r';
const char BLACK_KNIGHT = 'n';
const char BLACK_BISHOP = 'b';
const char BLACK_QUEEN = 'q';
const char BLACK_KING = 'k';

// FEN separator for strtok()
const char SEP[] = "/";

// Board characters
const char EMPTY = ' ';

/**************************************************************************************************
* Function name:        resetStruct
* Input:                char board as 2D array, PGN, Turn, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function reset values in the struct above, that won't re-written in
                        the next iteration. It initialize iSrc and jSrc to -1 in order to
                        differentiate between a location on the matrix (0) to an error (-1).
**************************************************************************************************/
void resetStruct(Move* pm) {

    pm->iSrc = -1; // bad initialization indicator
    pm->jSrc = -1; // bad initialization indicator
    pm->isCheck = 0;
    pm->isMate = 0;
    pm->isCapture = 0;
    pm->isPromotion = 0;
    pm->isLegal = 0;
    for ( int i = 0 ; i < SIZE ; i++ ) {
        for ( int j = 0 ; j < SIZE ; j++ ) {
            pm->pathBoard[i][j] = '0';
        }
    }
}

/**************************************************************************************************
* Function name:        toDigit
* Input:                single char from '0' to '9'
* Output:               single int (digit value)
* Function Operation:   converts given char into an int digit value
**************************************************************************************************/
int toDigit(char c) {
    assert('0' <= c && c <= '9');
    return c - '0';
}

/**************************************************************************************************
* Function name:        toIndex
* Input:                single char from 'a' to 'z'
* Output:               single int (for matrix's column int value)
* Function Operation:   converts given char into an int value for matrix's column
**************************************************************************************************/
int toIndex(char c) {
    assert('a' <= c && c <= 'z');
    return c - 'a';
}

/**************************************************************************************************
* Function name:        printColumns
* Input:                None
* Output:               None
* Function Operation:   prints columns - given by instructors
**************************************************************************************************/
void printColumns() {
    char column = toupper(FIRST_COL);
    printf("* |");
    for (int i = 0; i < SIZE; i++) {
        if (i) {
            printf(" ");
        }
        printf("%c", column);
        column++;
    }
    printf("| *\n");
}

/**************************************************************************************************
* Function name:        printSpacers
* Input:                None
* Output:               None
* Function Operation:   prints spaces - given by instructors
**************************************************************************************************/
void printSpacers() {
    printf("* -");
    for (int i = 0; i < SIZE; i++) {
        printf("--");
    }
    printf(" *\n");
}

/**************************************************************************************************
* Function name:        printRow
* Input:                None
* Output:               None
* Function Operation:   prints row - given by instructors
**************************************************************************************************/
void printRow(char row[], int rowIdx) {
    printf("%d ", rowIdx);
    int i = 0;
    while (row[i]) {
        if (isdigit(row[i])) {
            int spaces = toDigit(row[i++]);
            for (int j = 0; j < spaces; j++) {
                printf("|%c", EMPTY);
            }
        } else {
            printf("|%c", row[i++]);
        }
    }
    printf("| %d\n", rowIdx);
}

/**************************************************************************************************
* Function name:        printBoardFromFEN
* Input:                None
* Output:               None
* Function Operation:   prints board by given FEN - given by instructors
**************************************************************************************************/
void printBoardFromFEN(char fen[]) {
    printColumns();
    printSpacers();
    int rowIdx = SIZE;
    char* fenRow = strtok(fen, SEP);
    while (fenRow != NULL) {
        printRow(fenRow, rowIdx--);
        fenRow = strtok(NULL, SEP);
    }
    printSpacers();
    printColumns();
}

/**************************************************************************************************
* Function name:        createBoard
* Input:                char board as 2D array and char fen as 1D array
* Output:               None
* Function Operation:   this function is objective 1 of the assignment. It designed to parse the
                        FEN and build the game-board by storing values in board 2D array.
**************************************************************************************************/
void createBoard(char board[][SIZE], char fen[]) {
    // Variables declaration
    int loc = 0, i = 0, j = 0, num = 0;
    // A loop to parse the FEN
    while ( loc < strlen(fen) ) {
        if ( isdigit(fen[loc])) {
            num = toDigit(fen[loc]);
            for ( int k = 0 ; k < num ; k++ ) {
                board[i][j] = EMPTY;
                j++;
            }
        } else if ( fen[loc] == SEP[0] ) {
            i++;
            j = 0;
        } else {
            board[i][j] = fen[loc];
            j++;
        }
        loc++;
    }
}

/**************************************************************************************************
* Function name:        printBoard
* Input:                char board as 2D array
* Output:               the gaming board, according to the functions above
* Function Operation:   this function is objective 2 of the assignment. It uses functions above
                        and the created board 2D array to print the gaming board.
**************************************************************************************************/
void printBoard(char board[][SIZE]) {

    printColumns();
    printSpacers();
    for ( int i = 0 ; i < SIZE ; i++ ) {
        printf("%d ", SIZE-i);
        for ( int j = 0 ; j < SIZE ; j++ ) {
            printf("|%c", board[i][j]);
        }
        printf("| %d\n", SIZE-i);

    }
    printSpacers();
    printColumns();

}

/**************************************************************************************************
* Function name:        initSrcPiece
* Input:                the PGN as an array, the turn as int and a pointer to the struct above.
* Output:               None
* Function Operation:   initialize source gaming-piece.
**************************************************************************************************/
void initSrcPiece(char pgn[], int isWhiteTurn, Move *pm) {

    for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
        if ( pgn[0] == KING && isWhiteTurn ) {
            pm->srcPiece = WHITE_KING;
        } else if ( pgn[0] == KING && !isWhiteTurn ) {
            pm->srcPiece = BLACK_KING;
        } else if ( pgn[0] == QUEEN && isWhiteTurn ) {
            pm->srcPiece = WHITE_QUEEN;
        } else if ( pgn[0] == QUEEN && !isWhiteTurn ) {
            pm->srcPiece = BLACK_QUEEN;
        } else if ( pgn[0] == BISHOP && isWhiteTurn ) {
            pm->srcPiece = WHITE_BISHOP;
        } else if ( pgn[0] == BISHOP && !isWhiteTurn ) {
            pm->srcPiece = BLACK_BISHOP;
        } else if ( pgn[0] == KNIGHT && isWhiteTurn ) {
            pm->srcPiece = WHITE_KNIGHT;
        } else if ( pgn[0] == KNIGHT && !isWhiteTurn ) {
            pm->srcPiece = BLACK_KNIGHT;
        } else if ( pgn[0] == ROOK && isWhiteTurn ) {
            pm->srcPiece = WHITE_ROOK;
        } else if ( pgn[0] == ROOK && !isWhiteTurn ) {
            pm->srcPiece = BLACK_ROOK;
        } else {
            if ( isWhiteTurn ) {
                pm->srcPiece = WHITE_PAWN;
            } else if ( !isWhiteTurn ) {
                pm->srcPiece = BLACK_PAWN;
            }
        }
    }
}

/**************************************************************************************************
* Function name:        initDest
* Input:                the PGN as an array and a pointer to the struct above.
* Output:               None
* Function Operation:   initialize the move's destination.
**************************************************************************************************/
void initDest(char pgn[], Move* pm) {

    for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
        if ( islower(pgn[i]) && pgn[i] != 'x' ) {
            pm->jDest = toIndex(pgn[i]);
        } else if ( isdigit(pgn[i]) ) {
            pm->iDest = SIZE-toDigit(pgn[i]);
        }
    }
}

/**************************************************************************************************
* Function name:        initSpecAct
* Input:                the PGN as an array and a pointer to the struct above.
* Output:               if everything is okay, there won't be any output. if not, the function
                        will show an error massage.
* Function Operation:   scans the PGN and look for special activity signs suce as "x" for capture,
                        "+" for check, "#" for mate and "=" for promotion. if promotion sign found,
                        the function will continue to check for promotion type: "Q" for queen,
                        "N" for knight and so on.
**************************************************************************************************/
void initSpecAct(char pgn[], Move* pm) {

    // Parsing loop
    for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
        // Looking for signs in the PGN
        if ( pgn[i] == '+' ) {
            pm->isCheck = 1;
        } else if ( pgn[i] == '#' ) {
            pm->isMate = 1;
        } else if ( pgn[i] == 'x' ) {
            pm->isCapture = 1;
        } else if ( pgn[i] == '=' ) {
            pm->isPromotion = 1;
            // As instructed, we can assume that the PGN is valid so there is a [Q/N/B/R] after [=].
        }
    }
}

/**************************************************************************************************
* Function name:        typeOfPGN
* Input:                the PGN as an array.
* Output:               an integer that indicates the PGN type.
* Function Operation:   scans the PGN and classify it:
                         * Type 1 - one lowercase and one digit.
                         * Type 2 - one lowercase and two digit.
                         * Type 3 - two lowercase and one digit.
                         * Type 4 - two lowercase and two digit.
                        This function assists to initialize the source of the move.
**************************************************************************************************/
int typeOfPGN(char pgn[]) {

    int lower = 0, digit = 0;
    // Scan the PGN and count factors
    for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
        if ( islower(pgn[i]) && pgn[i] != 'x' ) {
            lower++;
        } else if ( isdigit(pgn[i]) ) {
            digit++;
        }
    }
    // Determine PGN type
    if ( lower == 1 && digit == 1) {
        return 1;
    } else if ( lower == 2 && digit == 1 ) {
        return 2;
    } else if ( lower == 1 && digit == 2 ) {
        return 3;
    } else if ( lower == 2 && digit == 2 ) {
        return 4;
    } else {
        return 0;
    }

}

/**************************************************************************************************
* Function name:        checkCell
* Input:                a char board as a 2D array and ints for row and column
* Output:               IS_EMPTY ( =0 ) for an empty cell
                        IS_WHITE ( =1 ) for a cell filled white piece
                        IS_BLACK ( -2 ) for a cell filled by black piece
* Function Operation:   check the cell in the location of the row and column given and return an
                        int, 0 for empty, 1 for white and 2 for black
**************************************************************************************************/
int checkCell(char board[][SIZE], int row, int column) {

    if ( row >= 0 && row < SIZE && column >= 0 && column < SIZE ) {
        if ( board[row][column] == EMPTY ) {
            return IS_EMPTY;
        } else if ( isupper(board[row][column]) ) {
            return IS_WHITE;
        } else if ( islower(board[row][column]) ) {
            return IS_BLACK;
        }
    }
}

/**************************************************************************************************
* Function name:        movementRules
* Input:                chars:  board as 2D array and the source piece.
                        ints:   source and destination as coordinates and if it is going to be a
                        capture move.
* Output:               1 for legal move (according to the "dry law" only) and 0 for illegal move.
* Function Operation:   gets all the input and check for each source gaming-piece if
                        it obey the rules of chess.
                        king    can move only one step but for any direction
                        rook    can move in a cross
                        bishop  can move in diagonals
                        queen   can move as a rook or as a bishop
                        knight  can move to specific cells
                        pawn    can move one step to the opponent direction, two
                                steps if it's source location as line 1 or SIZE-1
                                (on the matrix) and can capture only one step in
                                diagonal.
**************************************************************************************************/
int movementRules(char board[][SIZE], char srcPiece, int iSrc, int jSrc, int iDest, int jDest, int isCapture) {
    // calculating absolute value between source and destination
    int rowChange = abs(iDest-iSrc);
    int colChange = abs(jDest-jSrc);
    // Determine threshold condition
    if ( iSrc == -1 || jSrc == -1 ) {
        return 0;
    }
    // A king can move only one step but for any direction
    if ( (srcPiece == WHITE_KING) || (srcPiece == BLACK_KING) ) {
        if ( rowChange <= 1 && colChange <= 1 ) {
                return 1;
            } else {
                return 0;
            }
    // A queen can move in a cross or diagonals
    } else if ( (srcPiece == WHITE_QUEEN) || (srcPiece == BLACK_QUEEN) ) {
        if ( (rowChange == colChange) || (iDest == iSrc) || (jDest == jSrc) ) {
                return 1;
            } else {
                return 0;
            }
    // A bishop can move in diagonals
    } else if ( (srcPiece == WHITE_BISHOP) || (srcPiece == BLACK_BISHOP) ) {
        if ( rowChange == colChange ) {
                return 1;
            } else {
                return 0;
            }
    // A bishop can move in a cross
    } else if ( (srcPiece == WHITE_ROOK) || (srcPiece == BLACK_ROOK) ) {
        if ( (iDest == iSrc) || (jDest == jSrc ) ) {
                return 1;
            } else {
                return 0;
            }
    // Knight's movements in row and column are sum to 3 but non of the movements are 0.
    } else if ( (srcPiece == WHITE_KNIGHT) || (srcPiece == BLACK_KNIGHT) ) {
        if ( (rowChange + colChange == 3) && (rowChange != 0) && (colChange != 0) ) {
                return 1;
            } else {
                return 0;
            }
    // A pawn can move to the opponent direction with several rules so each pawn have to be programmed separately.
    } else if ( srcPiece == WHITE_PAWN ) {
        if ( (iSrc-iDest == 1) && (jSrc == jDest) ) {
            return 1;
        } else if ( (iSrc == SIZE-2) && (iDest == SIZE-4) && (jDest == jSrc) && (iSrc > 0) ) {
            return 1;
        } else if ( (isCapture && (iSrc-iDest == 1))
                   && ( ((checkCell(board, iSrc-1, jSrc+1) == IS_BLACK)
                         && (checkCell(board, iSrc-1, jSrc-1) == IS_BLACK) && (colChange <= 1))
                       || ((checkCell(board, iSrc-1, jSrc-1) == IS_BLACK) && (jSrc-jDest == 1))
                       || ((checkCell(board, iSrc-1, jSrc+1) == IS_BLACK) && (jDest-jSrc == 1)) ) ) {
            return 1;
        } else {
            return 0;
        }
    } else if ( srcPiece == BLACK_PAWN ) {
        if ( (iDest-iSrc == 1) && (jSrc == jDest) ) {
            return 1;
        } else if ( (iSrc == 1) && (iDest == 3) && (jSrc == jDest) && (iSrc < SIZE) ) {
            return 1;
        } else if ( (isCapture && (iDest-iSrc == 1))
                   && ( ((checkCell(board, iSrc+1, jSrc+1) == IS_WHITE)
                         && (checkCell(board, iSrc+1, jSrc-1) == IS_WHITE) && (colChange <= 1))
                       || ((checkCell(board, iSrc+1, jSrc-1) == IS_WHITE) && (jSrc-jDest == 1))
                       || ((checkCell(board, iSrc+1, jSrc+1) == IS_WHITE) && (jDest-jSrc == 1)) ) ) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }

}

/**************************************************************************************************
* Function name:        wayIsClear
* Input:                board as 2D array source, destination and Move m.
* Output:               1 - way is clear, 0 - it isn't
* Function Operation:   this function check for other game-pieces on the path between source and
                        destination of the source piece. If it finds any. it will return 0.
**************************************************************************************************/
int wayIsClear(char board[][SIZE], int checkRow, int checkCol, Move m) {

    if ( m.srcPiece == WHITE_ROOK || m.srcPiece == BLACK_ROOK ) {
        // Coming from North
        if ( checkRow < m.iDest && checkCol == m.jDest ) {
            for ( int i = checkRow+1 ; i < m.iDest ; i++ ) {
                if (checkCell(board, i, m.jDest) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from South
        else if ( checkRow > m.iDest && checkCol == m.jDest ) {
            for ( int i = checkRow-1 ; i > m.iDest ; i-- ) {
                if (checkCell(board, i, m.jDest) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from East
        else if ( checkRow == m.iDest && checkCol > m.jDest ) {
            for ( int j = checkCol-1 ; j > m.jDest ; j-- ) {
                if (checkCell(board, m.iDest, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from West
        else if ( checkRow == m.iDest && checkCol < m.jDest ) {
            for ( int j = checkCol+1 ; j < m.jDest ; j++ ) {
                if (checkCell(board, m.iDest, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
    } else if ( m.srcPiece == WHITE_BISHOP || m.srcPiece == BLACK_BISHOP ) {
        // Coming from NE
        if ( checkRow < m.iDest && checkCol > m.jDest && abs((checkCol-m.jDest)/(checkRow-m.iDest)) == 1 ) {
            for ( int i = checkRow+1 , j = checkCol-1 ; i < m.iDest , j > m.jDest ; i++ , j-- ) {
                if (checkCell(board, i, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from SE
        else if ( checkRow > m.iDest && checkCol > m.jDest && abs((checkCol-m.jDest)/(checkRow-m.iDest)) == 1 ) {
            for ( int i = checkRow-1 , j = checkCol-1 ; i > m.iDest , j > m.jDest ; i-- , j-- ) {
                if (checkCell(board, i, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Look SW
        else if ( checkRow > m.iDest && checkCol < m.jDest && abs((checkCol-m.jDest)/(checkRow-m.iDest)) == 1 ) {
            for ( int i = checkRow-1 , j = checkCol+1 ; i > m.iDest , j < m.jDest ; i-- , j++ ) {
                if (checkCell(board, i, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Look NW
        else if ( checkRow < m.iDest && checkCol < m.jDest && abs((checkCol-m.jDest)/(checkRow-m.iDest)) == 1 ) {
            for ( int i = checkRow+1 , j = checkCol+1 ; i < m.iDest , j < m.jDest ; i++ , j++ ) {
                if (checkCell(board, i, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
    } else if ( m.srcPiece == WHITE_QUEEN || m.srcPiece == BLACK_QUEEN ) {
        // Coming from North
        if ( checkRow < m.iDest && checkCol == m.jDest ) {
            for ( int i = checkRow+1 ; i < m.iDest ; i++ ) {
                if (checkCell(board, i, m.jDest) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from South
        else if ( checkRow > m.iDest && checkCol == m.jDest ) {
            for ( int i = checkRow-1 ; i > m.iDest ; i-- ) {
                if (checkCell(board, i, m.jDest) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from East
        else if ( checkRow == m.iDest && checkCol > m.jDest ) {
            for ( int j = checkCol-1 ; j > m.jDest ; j-- ) {
                if (checkCell(board, m.iDest, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from West
        else if ( checkRow == m.iDest && checkCol < m.jDest ) {
            for ( int j = checkCol+1 ; j < m.jDest ; j++ ) {
                if (checkCell(board, m.iDest, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from NE
        if ( checkRow < m.iDest && checkCol > m.jDest && abs((checkCol-m.jDest)/(checkRow-m.iDest)) == 1 ) {
            for ( int i = checkRow+1 , j = checkCol-1 ; i < m.iDest , j > m.jDest ; i++ , j-- ) {
                if (checkCell(board, i, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Coming from SE
        else if ( checkRow > m.iDest && checkCol > m.jDest && abs((checkCol-m.jDest)/(checkRow-m.iDest)) == 1 ) {
            for ( int i = checkRow-1 , j = checkCol-1 ; i > m.iDest , j > m.jDest ; i-- , j-- ) {
                if (checkCell(board, i, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Look SW
        else if ( checkRow > m.iDest && checkCol < m.jDest && abs((checkCol-m.jDest)/(checkRow-m.iDest)) == 1 ) {
            for ( int i = checkRow-1 , j = checkCol+1 ; i > m.iDest , j < m.jDest ; i-- , j++ ) {
                if (checkCell(board, i, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }
        // Look NW
        else if ( checkRow < m.iDest && checkCol < m.jDest && abs((checkCol-m.jDest)/(checkRow-m.iDest)) == 1 ) {
            for ( int i = checkRow+1 , j = checkCol+1 ; i < m.iDest , j < m.jDest ; i++ , j++ ) {
                if (checkCell(board, i, j) != IS_EMPTY) {
                    return 0;
                }
            }
            return 1;
        }

    } else if ( m.srcPiece == WHITE_PAWN ) {
        if ( (checkRow-m.iDest == 2) && (checkCell(board, checkRow-1, m.jDest) != IS_EMPTY) ) {
            return 0;
        } else {
            return 1;
        }
    } else if ( m.srcPiece == BLACK_PAWN ) {
        if ( (m.iDest-checkRow == 2) && (checkCell(board, checkRow+1, m.jDest) != IS_EMPTY) ) {
            return 0;
        } else {
            return 1;
        }
    } else if ( m.srcPiece == WHITE_KING || m.srcPiece == BLACK_KING ) {
        // Only 1 king exist on the board (for each side) so only 1 king can go to destination
        return 1;
    } else if ( m.srcPiece == WHITE_KNIGHT || m.srcPiece == BLACK_KNIGHT ) {
        // Knights skips cells so no piece can stand on their way.
        return 1;
    }


}


/**************************************************************************************************
* Function name:        initSrc
* Input:                char board as 2D array, PGN, Turn, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function use TypeOfPGN function to identify PGN type. It initialize
                        the source coordinations by PGN, by board, or by both - depends on the
                        type of the PGN.
**************************************************************************************************/
void initSrc(char board[][SIZE], char pgn[], int isWhiteTurn, Move* pm, Move m) {

    int type = typeOfPGN(pgn);
    int iSrc, jSrc;

    if ( isWhiteTurn ) {

        switch (type) {

            case 1: for ( int i = 0 ; i < SIZE ; i++ ) {
                        for ( int j = 0 ; j < SIZE ; j++ ) {
                            if ( movementRules(board, m.srcPiece, i, j, m.iDest, m.jDest, m.isCapture)
                                && (board[i][j] == m.srcPiece) && wayIsClear(board, i, j, m) ) {
                                pm->iSrc = i;
                                pm->jSrc = j;
                                return;
                            }
                        }
                    }
                    break;

            case 2: for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
                        if ( islower(pgn[i]) ) {
                            pm->jSrc = toIndex(pgn[i]);
                            jSrc = toIndex(pgn[i]);
                            break;
                        }
                    }
                    for ( int i = 0 ; i < SIZE ; i++ ) {
                        if ( movementRules(board, m.srcPiece, i, jSrc, m.iDest, m.jDest, m.isCapture)
                            && (board[i][jSrc] == m.srcPiece) && wayIsClear(board, i, jSrc, m) ) {
                            pm->iSrc = i;
                            return;
                        }
                    }
                    break;

            case 3: for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
                        if ( isdigit(pgn[i]) ) {
                            pm->iSrc = toDigit(pgn[i]);
                            iSrc = toDigit(pgn[i]);
                            break;
                        }
                    }
                    for ( int j = 0 ; j < SIZE ; j++ ) {
                        if ( movementRules(board, m.srcPiece, iSrc, j, m.iDest, m.jDest, m.isCapture)
                            && (board[iSrc][j] == m.srcPiece) && wayIsClear(board, iSrc, j, m) ) {
                            pm->jSrc = j;
                            return;
                        }
                    }
                    break;

            case 4: for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
                        if ( islower(pgn[i]) ) {
                            pm->jSrc = toIndex(pgn[i]);
                        } else if ( isdigit(pgn[i]) ) {
                            pm->iSrc = SIZE-toDigit(pgn[i]);
                            return;
                        }
                    }
                    break;

            default:
                    printf("\nError: PGN in invalid.");
        }

    } else if ( !isWhiteTurn ) {

        switch (type) {

            case 1: for ( int i = 0 ; i < SIZE ; i++ ) {
                        for ( int j = 0 ; j < SIZE ; j++ ) {
                            if ( movementRules(board, m.srcPiece, i, j, m.iDest, m.jDest, m.isCapture)
                                && (board[i][j] == m.srcPiece) && wayIsClear(board, i, j, m) ) {
                                pm->iSrc = i;
                                pm->jSrc = j;
                                return;
                            }
                        }
                    }
                    break;

            case 2: for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
                        if ( islower(pgn[i]) ) {
                            pm->jSrc = toIndex(pgn[i]);
                            jSrc = toIndex(pgn[i]);
                            break;
                        }
                    }
                    for ( int i = 0 ; i < SIZE ; i++ ) {
                        if ( movementRules(board, m.srcPiece, i, jSrc, m.iDest, m.jDest, m.isCapture)
                            && (board[i][jSrc] == m.srcPiece) && wayIsClear(board, i, jSrc, m) ) {
                            pm->iSrc = i;
                            return;
                        }
                    }
                    break;

            case 3: for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
                        if ( isdigit(pgn[i]) ) {
                            pm->iSrc = toDigit(pgn[i]);
                            iSrc = toDigit(pgn[i]);
                            break;
                        }
                    }
                    for ( int j = 0 ; j < SIZE ; j++ ) {
                        if ( movementRules(board, m.srcPiece, iSrc, j, m.iDest, m.jDest, m.isCapture)
                            && (board[iSrc][j] == m.srcPiece) && wayIsClear(board, iSrc, j, m) ) {
                            pm->jSrc = j;
                            return;
                        }
                    }
                    break;

            case 4: for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
                        if ( islower(pgn[i]) ) {
                            pm->jSrc = toIndex(pgn[i]);
                        } else if ( isdigit(pgn[i]) ) {
                            pm->iSrc = SIZE-toDigit(pgn[i]);
                            return;
                        }
                    }
                    break;

            default:
                    printf("\nError: PGN in invalid.");
        }


    }

}

/**************************************************************************************************
* Function name:        initBoardCopy
* Input:                char board as 2D array and a pointer to the struct above.
* Output:               None
* Function Operation:   clone the gaming board in order to make changes and analyze consequences.
**************************************************************************************************/
void initBoardCopy(char board[][SIZE], Move* pm) {

    for ( int i = 0 ; i < SIZE ; i++ ) {
        for ( int j = 0 ; j < SIZE ; j ++ ) {
            pm->boardCopy[i][j] = board[i][j];
        }
    }
}

/**************************************************************************************************
* Function name:        initPathBoard
* Input:                char board as 2D array, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   store 1 in every location in the array that the source piece can move to
                        according to movementRules function (according to the "dry law"). This
                        function determine if the next move obey movementRules and also helps to
                        visualize the possible moves of a character.
**************************************************************************************************/
void initPathBoard(char board[][SIZE], Move m, Move* pm) {

    int temp = 0;
    for ( int i = 0 ; i < SIZE ; i++ ) {
        for ( int j = 0 ; j < SIZE ; j ++ ) {
            temp = movementRules(board, m.srcPiece, m.iSrc, m.jSrc, i, j, m.isCapture);
            if ( temp == 1 ) {
                pm->pathBoard[i][j] = '1';
            } else {
                pm->pathBoard[i][j] = '-';
            }
        }
    }
}

/**************************************************************************************************
* Function name:        checkPawnPath
* Input:                char board as 2D array, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function uses the pathBoard, a board that stores 1's at the locations
                        that the game-piece can go "by law", and board, the original game-board,
                        and look for a correlation between "1" in the pathBoard and other game-
                        piece on the original board. Namely, look for other game-pieces on the
                        source piece path. If a correlation been found the function will write an
                        "x" to the relevant location on pathBoard. In the end, the gaming piece
                        will be allowed to move only to locations marked as "1" ("X" is only for
                        development uses).

                        This function specifically designed to the Pawn.
**************************************************************************************************/
void checkPawnPath(char board[][SIZE], Move m, Move* pm) {

    if ( m.srcPiece == WHITE_PAWN ) {

        if ( (m.iSrc == SIZE-2) && (checkCell(board, m.iSrc-1, m.jSrc) != IS_EMPTY) ) {
            pm->pathBoard[m.iSrc-1][m.jSrc] = 'X';
            pm->pathBoard[m.iSrc-2][m.jSrc] = 'X';
        } else if ( (m.iSrc == SIZE-2) && (checkCell(board, m.iSrc-2, m.jSrc) != IS_EMPTY) ) {
            pm->pathBoard[m.iSrc-2][m.jSrc] = 'X';
        } else if ( (m.iSrc > 0) && (checkCell(board, m.iSrc-1, m.jSrc) != IS_EMPTY) ) {
            pm->pathBoard[m.iSrc-1][m.jSrc] = 'X';
        }
    } else if ( m.srcPiece == BLACK_PAWN ) {

        if ( (m.iSrc == 1) && (checkCell(board, m.iSrc+1, m.jSrc) != IS_EMPTY) ) {
            pm->pathBoard[m.iSrc+1][m.jSrc] = 'X';
            pm->pathBoard[m.iSrc+2][m.jSrc] = 'X';
        } else if ( (m.iSrc == 1) && (checkCell(board, m.iSrc+2, m.jSrc) != IS_EMPTY) ) {
            pm->pathBoard[m.iSrc+2][m.jSrc] = 'X';
        } else if ( (m.iSrc < SIZE-1 ) && (checkCell(board, m.iSrc+1, m.jSrc) != IS_EMPTY) ) {
            pm->pathBoard[m.iSrc+1][m.jSrc] = 'X';
        }
    }

}

/**************************************************************************************************
* Function name:        checkKnightPath
* Input:                char board as 2D array, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function uses the pathBoard, a board that stores 1's at the locations
                        that the game-piece can go "by law", and board, the original game-board,
                        and look for a correlation between "1" in the pathBoard and other game-
                        piece on the original board. Namely, look for other game-pieces on the
                        source piece path. If a correlation been found the function will write an
                        "x" to the relevant location on pathBoard. In the end, the gaming piece
                        will be allowed to move only to locations marked as "1" ("X" is only for
                        development uses).

                        This function specifically designed to the Knight.
**************************************************************************************************/
void checkKnightPath(char board[][SIZE], Move m, Move* pm) {

    if ( m.srcPiece == WHITE_KNIGHT ) {
        pm->pathBoard[m.iSrc][m.jSrc] = 'X';
        if ( checkCell(board, m.iSrc-2, m.jSrc-1) == IS_WHITE ) {
            pm->pathBoard[m.iSrc-2][m.jSrc-1] = 'X';
        }
        if ( checkCell(board, m.iSrc-2, m.jSrc+1) == IS_WHITE ) {
            pm->pathBoard[m.iSrc-2][m.jSrc+1] = 'X';
        }
        if ( checkCell(board, m.iSrc-1, m.jSrc+2) == IS_WHITE ) {
            pm->pathBoard[m.iSrc-1][m.jSrc+2] = 'X';
        }
        if ( checkCell(board, m.iSrc+1, m.jSrc+2) == IS_WHITE ) {
            pm->pathBoard[m.iSrc+1][m.jSrc+2] = 'X';
        }
        if ( checkCell(board, m.iSrc+2, m.jSrc+1) == IS_WHITE ) {
            pm->pathBoard[m.iSrc+2][m.jSrc+1] = 'X';
        }
        if ( checkCell(board, m.iSrc+2, m.jSrc-1) == IS_WHITE ) {
            pm->pathBoard[m.iSrc+2][m.jSrc-1] = 'X';
        }
        if ( checkCell(board, m.iSrc+1, m.jSrc-2) == IS_WHITE ) {
            pm->pathBoard[m.iSrc+1][m.jSrc-2] = 'X';
        }
        if ( checkCell(board, m.iSrc-1, m.jSrc-2) == IS_WHITE ) {
            pm->pathBoard[m.iSrc-1][m.jSrc-2] = 'X';
        }
        if ( checkCell(board, m.iSrc-2, m.jSrc-1) == IS_WHITE ) {
            pm->pathBoard[m.iSrc-2][m.jSrc-1] = 'X';
        }
    } else if ( m.srcPiece == BLACK_KNIGHT ) {
        pm->pathBoard[m.iSrc][m.jSrc] = 'X';
        if ( checkCell(board, m.iSrc-2, m.jSrc-1) == IS_BLACK ) {
            pm->pathBoard[m.iSrc-2][m.jSrc-1] = 'X';
        }
        if ( checkCell(board, m.iSrc-2, m.jSrc+1) == IS_BLACK ) {
            pm->pathBoard[m.iSrc-2][m.jSrc+1] = 'X';
        }
        if ( checkCell(board, m.iSrc-1, m.jSrc+2) == IS_BLACK ) {
            pm->pathBoard[m.iSrc-1][m.jSrc+2] = 'X';
        }
        if ( checkCell(board, m.iSrc+1, m.jSrc+2) == IS_BLACK ) {
            pm->pathBoard[m.iSrc+1][m.jSrc+2] = 'X';
        }
        if ( checkCell(board, m.iSrc+2, m.jSrc+1) == IS_BLACK ) {
            pm->pathBoard[m.iSrc+2][m.jSrc+1] = 'X';
        }
        if ( checkCell(board, m.iSrc+2, m.jSrc-1) == IS_BLACK ) {
            pm->pathBoard[m.iSrc+2][m.jSrc-1] = 'X';
        }
        if ( checkCell(board, m.iSrc+1, m.jSrc-2) == IS_BLACK ) {
            pm->pathBoard[m.iSrc+1][m.jSrc-2] = 'X';
        }
        if ( checkCell(board, m.iSrc-1, m.jSrc-2) == IS_BLACK ) {
            pm->pathBoard[m.iSrc-1][m.jSrc-2] = 'X';
        }
        if ( checkCell(board, m.iSrc-2, m.jSrc-1) == IS_BLACK ) {
            pm->pathBoard[m.iSrc-2][m.jSrc-1] = 'X';
        }
    }
}

/**************************************************************************************************
* Function name:        checkKingPath
* Input:                char board as 2D array, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function uses the pathBoard, a board that stores 1's at the locations
                        that the game-piece can go "by law", and board, the original game-board,
                        and look for a correlation between "1" in the pathBoard and other game-
                        piece on the original board. Namely, look for other game-pieces on the
                        source piece path. If a correlation been found the function will write an
                        "x" to the relevant location on pathBoard. In the end, the gaming piece
                        will be allowed to move only to locations marked as "1" ("X" is only for
                        development uses).

                        This function specifically designed to the King.
**************************************************************************************************/
void checkKingPath(char board[][SIZE], Move m, Move* pm) {

    if ( m.srcPiece == WHITE_KING ) {
        for ( int i = m.iSrc-1 ; i <= m.iSrc+1 ; i++ ) {
            for ( int j = m.jSrc-1 ; j < m.jSrc+1 ; j++ ) {
                if ( checkCell(board, i, j) == IS_WHITE ) {
                    pm->pathBoard[i][j] = 'X';
                }
            }
        }
    } else if ( m.srcPiece == BLACK_KING ) {
        for ( int i = m.iSrc-1 ; i <= m.iSrc+1 ; i++ ) {
            for ( int j = m.jSrc-1 ; j < m.jSrc+1 ; j++ ) {
                 if ( checkCell(board, i, j) == IS_BLACK ) {
                    pm->pathBoard[i][j] = 'X';
                 }
            }
        }
    }
}

/**************************************************************************************************
* Function name:        checkRookPath
* Input:                char board as 2D array, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function uses the pathBoard, a board that stores 1's at the locations
                        that the game-piece can go "by law", and board, the original game-board,
                        and look for a correlation between "1" in the pathBoard and other game-
                        piece on the original board. Namely, look for other game-pieces on the
                        source piece path. If a correlation been found the function will write an
                        "x" to the relevant location on pathBoard. In the end, the gaming piece
                        will be allowed to move only to locations marked as "1" ("X" is only for
                        development uses).

                        This function specifically designed to the Rook.
**************************************************************************************************/
void checkRookPath(char board[][SIZE], char localSrcPiece, Move m, Move* pm) {

    pm->pathBoard[m.iSrc][m.jSrc] = 'X';

    if ( localSrcPiece == WHITE_ROOK ) {
        for ( int i = m.iSrc+1 ; i < SIZE ; i++ ) {
            if ( checkCell(board, i, m.jSrc) == IS_WHITE ) {
                for ( int k = i ; k < SIZE ; k++ ) {
                    pm->pathBoard[k][m.jSrc] = 'X';
                }
                break;
            } else if ( checkCell(board, i, m.jSrc) == IS_BLACK ) {
                for ( int k = i+1 ; k < SIZE ; k++ ) {
                    pm->pathBoard[k][m.jSrc] = 'X';
                }
                break;
            }
        }
        for ( int i = m.iSrc-1 ; i >= 0 ; i-- ) {
            if ( checkCell(board, i, m.jSrc) == IS_WHITE ) {
                for ( int k = i ; k >= 0 ; k-- ) {
                    pm->pathBoard[k][m.jSrc] = 'X';
                }
                break;
            } else if ( checkCell(board, i, m.jSrc) == IS_BLACK ) {
                for ( int k = i-1 ; k >= 0 ; k-- ) {
                    pm->pathBoard[k][m.jSrc] = 'X';
                }
                break;
            }
        }
        for ( int j = m.jSrc+1 ; j < SIZE ; j++ ) {
            if ( checkCell(board, m.iSrc, j) == IS_WHITE ) {
                for ( int k = j ; k < SIZE ; k++ ) {
                    pm->pathBoard[m.iSrc][k] = 'X';
                }
                break;
            } else if ( checkCell(board, m.iSrc, j) == IS_BLACK ) {
                for ( int k = j+1 ; k < SIZE ; k++ ) {
                    pm->pathBoard[m.iSrc][k] = 'X';
                }
                break;
            }
        }
        for ( int j = m.jSrc-1 ; j >= 0 ; j-- ) {
            if ( checkCell(board, m.iSrc, j) == IS_WHITE ) {
                for ( int k = j ; k >= 0 ; k-- ) {
                    pm->pathBoard[m.iSrc][k] = 'X';
                }
                break;
            } else if ( checkCell(board, m.iSrc, j) == IS_BLACK ) {
                for ( int k = j-1 ; k >= 0 ; k-- ) {
                    pm->pathBoard[m.iSrc][k] = 'X';
                }
                break;
            }
        }
    } else if ( localSrcPiece == BLACK_ROOK ) {
        for ( int i = m.iSrc+1 ; i < SIZE ; i++ ) {
            if ( checkCell(board, i, m.jSrc) == IS_BLACK ) {
                for ( int k = i ; k < SIZE ; k++ ) {
                    pm->pathBoard[k][m.jSrc] = 'X';
                }
                break;
            } else if ( checkCell(board, i, m.jSrc) == IS_WHITE ) {
                for ( int k = i+1 ; k < SIZE ; k++ ) {
                    pm->pathBoard[k][m.jSrc] = 'X';
                }
                break;
            }
        }
        for ( int i = m.iSrc-1 ; i >= 0 ; i-- ) {
            if ( checkCell(board, i, m.jSrc) == IS_BLACK ) {
                for ( int k = i ; k >= 0 ; k-- ) {
                    pm->pathBoard[k][m.jSrc] = 'X';
                }
                break;
            } else if ( checkCell(board, i, m.jSrc) == IS_WHITE ) {
                for ( int k = i-1 ; k >= 0 ; k-- ) {
                    pm->pathBoard[k][m.jSrc] = 'X';
                }
                break;
            }
        }
        for ( int j = m.jSrc+1 ; j < SIZE ; j++ ) {
            if ( checkCell(board, m.iSrc, j) == IS_BLACK ) {
                for ( int k = j ; k < SIZE ; k++ ) {
                    pm->pathBoard[m.iSrc][k] = 'X';
                }
                break;
            } else if ( checkCell(board, m.iSrc, j) == IS_WHITE ) {
                for ( int k = j+1 ; k < SIZE ; k++ ) {
                    pm->pathBoard[m.iSrc][k] = 'X';
                }
                break;
            }
        }
        for ( int j = m.jSrc-1 ; j >= 0 ; j-- ) {
            if ( checkCell(board, m.iSrc, j) == IS_BLACK ) {
                for ( int k = j ; k >= 0 ; k-- ) {
                    pm->pathBoard[m.iSrc][k] = 'X';
                }
                break;
            } else if ( checkCell(board, m.iSrc, j) == IS_WHITE ) {
                for ( int k = j-1 ; k >= 0 ; k-- ) {
                    pm->pathBoard[m.iSrc][k] = 'X';
                }
                break;
            }
        }
    }
}

/**************************************************************************************************
* Function name:        checkBishopPath
* Input:                char board as 2D array, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function uses the pathBoard, a board that stores 1's at the locations
                        that the game-piece can go "by law", and board, the original game-board,
                        and look for a correlation between "1" in the pathBoard and other game-
                        piece on the original board. Namely, look for other game-pieces on the
                        source piece path. If a correlation been found the function will write an
                        "x" to the relevant location on pathBoard. In the end, the gaming piece
                        will be allowed to move only to locations marked as "1" ("X" is only for
                        development uses).


                        This function specifically designed to the Bishop.
**************************************************************************************************/
void checkBishopPath(char board[][SIZE], char localSrcPiece, Move m, Move* pm) {

    pm->pathBoard[m.iSrc][m.jSrc] = 'X';

    if ( localSrcPiece == WHITE_BISHOP ) {

        for ( int i = m.iSrc-1, j = m.jSrc-1 ; (i >= 0) && (j >= 0) ; i--, j-- ) {
            if (checkCell(board, i, j) == IS_WHITE ) {
                for ( i, j ; (i >= 0) && (j >= 0) ; i--, j-- ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            } else if ( checkCell(board, i, j) == IS_BLACK ) {
                for ( i-=1, j-=1 ; (i >= 0) && (j >= 0) ; i--, j-- ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            }
        } for ( int i = m.iSrc-1, j = m.jSrc+1 ; (i >= 0) && (j < SIZE) ; i--, j++ ) {
            if ( checkCell(board, i, j) == IS_WHITE ) {
                for ( i, j ; (i >= 0) && (j < SIZE) ; i--, j++ ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            } else if ( checkCell(board, i, j) == IS_BLACK ) {
                for ( i-=1, j+=1 ; (i >= 0) && (j < SIZE) ; i--, j++ ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            }
        }
        for ( int i = m.iSrc+1, j = m.jSrc+1 ; (i < SIZE) && (j < SIZE) ; i++, j++ ) {
            if ( checkCell(board, i, j) == IS_WHITE ) {
                for ( i, j ; (i < SIZE) && (j < SIZE) ; i++, j++ ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            } else if ( checkCell(board, i, j) == IS_BLACK ) {
                for ( i+=1, j+=1 ; (i < SIZE) && (j < SIZE) ; i++, j++ ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            }
        }
        for ( int i = m.iSrc+1, j = m.jSrc-1 ; (i < SIZE) && (j >= 0) ; i++, j-- ) {
            if ( checkCell(board, i, j) == IS_WHITE ) {
                for ( i, j ; (i < SIZE) && (j >= 0) ; i++, j-- ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            } else if ( checkCell(board, i, j) == IS_BLACK ) {
                for ( i+=1, j-=1 ; (i <SIZE) && (j >= 0) ; i++, j-- ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            }
        }

    } else if ( localSrcPiece == BLACK_BISHOP ) {

        for ( int i = m.iSrc-1, j = m.jSrc-1 ; (i >= 0) && (j >= 0) ; i--, j-- ) {
            if ( checkCell(board, i, j) == IS_BLACK ) {
                for ( i, j ; (i >= 0) && (j >= 0) ; i--, j-- ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            } else if ( checkCell(board, i, j) == IS_WHITE ) {
                for ( i-=1, j-=1 ; (i >= 0) && (j >= 0) ; i--, j-- ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            }
        } for ( int i = m.iSrc-1, j = m.jSrc+1 ; (i >= 0) && (j < SIZE) ; i--, j++ ) {
            if ( checkCell(board, i, j) == IS_BLACK ) {
                for ( i, j ; (i >= 0) && (j < SIZE) ; i--, j++ ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            } else if ( checkCell(board, i, j) == IS_WHITE ) {
                for ( i-=1, j+=1 ; (i >= 0) && (j < SIZE) ; i--, j++ ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            }
        }
        for ( int i = m.iSrc+1, j = m.jSrc+1 ; (i < SIZE) && (j < SIZE) ; i++, j++ ) {
            if ( checkCell(board, i, j) == IS_BLACK ) {
                for ( i, j ; (i < SIZE) && (j < SIZE) ; i++, j++ ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            } else if ( checkCell(board, i, j) == IS_WHITE ) {
                for ( i+=1, j+=1 ; (i < SIZE) && (j < SIZE) ; i++, j++ ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            }
        }
        for ( int i = m.iSrc+1, j = m.jSrc-1 ; (i < SIZE) && (j >= 0) ; i++, j-- ) {
            if ( checkCell(board, i, j) == IS_BLACK ) {
                for ( i, j ; (i < SIZE) && (j >= 0) ; i++, j-- ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            } else if ( checkCell(board, i, j) == IS_WHITE ) {
                for ( i+=1, j-=1 ; (i <SIZE) && (j >= 0) ; i++, j-- ) {
                    pm->pathBoard[i][j] = 'X';
                }
                break;
            }
        }
    }
}

/**************************************************************************************************
* Function name:        checkQueenPath
* Input:                char board as 2D array, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function uses the pathBoard, a board that stores 1's at the locations
                        that the game-piece can go "by law", and board, the original game-board,
                        and look for a correlation between "1" in the pathBoard and other game-
                        piece on the original board. Namely, look for other game-pieces on the
                        source piece path. If a correlation been found the function will write an
                        "x" to the relevant location on pathBoard. In the end, the gaming piece
                        will be allowed to move only to locations marked as "1" ("X" is only for
                        development uses).

                        This function specifically designed to the Queen and it consist of the
                        functions: checkRookPath and checkBishopPath.
**************************************************************************************************/
void checkQueenPath(char board[][SIZE], Move m, Move* pm) {

    if ( m.srcPiece == WHITE_QUEEN ) {
        checkRookPath(board, WHITE_ROOK, m, pm);
        checkBishopPath(board, WHITE_BISHOP, m, pm);
    } else if ( m.srcPiece == BLACK_QUEEN ) {
        checkRookPath(board, BLACK_ROOK, m, pm);
        checkBishopPath(board, BLACK_BISHOP, m, pm);
    }
}

/**************************************************************************************************
* Function name:        updatePathBoard
* Input:                char board as 2D array, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   This function determine which "check-path" function to activate according
                        to the source piece.
**************************************************************************************************/
void updatePathBoard(char board[][SIZE], Move m, Move* pm) {

    if ( (m.srcPiece == WHITE_PAWN) || (m.srcPiece == BLACK_PAWN) ) {
        checkPawnPath(board, m, pm);
    } else if ( (m.srcPiece == WHITE_KING) || (m.srcPiece == BLACK_KING)  ) {
        checkKingPath(board, m, pm);
    } else if ( (m.srcPiece == WHITE_QUEEN) || (m.srcPiece == BLACK_QUEEN)  ) {
        checkQueenPath(board, m, pm);
    } else if ( m.srcPiece == WHITE_ROOK ) {
        checkRookPath(board, WHITE_ROOK, m, pm);
    } else if ( m.srcPiece == BLACK_ROOK ) {
        checkRookPath(board, BLACK_ROOK, m, pm);
    } else if ( m.srcPiece == WHITE_BISHOP ) {
        checkBishopPath(board, WHITE_BISHOP, m, pm);
    } else if ( m.srcPiece == BLACK_BISHOP ) {
        checkBishopPath(board, BLACK_BISHOP, m, pm);
    } else if ( (m.srcPiece == WHITE_KNIGHT) || (m.srcPiece == BLACK_KNIGHT) ) {
        checkKnightPath(board, m, pm);
    }
}

/**************************************************************************************************
* Function name:        canGo
* Input:                char board as 2D array and Move struct.
* Output:               1 or 0 (int).
* Function Operation:   This function check given location on pathBoard and return 1 (int) if it
                        found an "1" (char) or 0 (int) of not. It is designed to make the
                        following code more readable.
**************************************************************************************************/
int canGo(char board[][SIZE], Move m) {

    if ( m.pathBoard[m.iDest][m.jDest] == '1' ) {
        return 1;
    } else {
        return 0;
    }
}

/**************************************************************************************************
* Function name:        promotion
* Input:                char board as 2D array, char PGN, Move struct and pointer to the struct.
* Output:               None.
* Function Operation:   if "specAct()" function found a promotion sign in the PGN, ("="), this
                        function will look for the promotion sign (that have to be in the PGN
                        because "specAct()" verified it already) and execute the relevant
                        promotion in the boardCopy.
**************************************************************************************************/
void promotion(char board[][SIZE], char pgn[], Move m, Move* pm) {

    if ( (m.isPromotion) && (m.srcPiece == WHITE_PAWN) && (m.iDest == 0) ) {
        for ( int i = 2 ; i < strlen(pgn) ; i++ ) {
            if ( pgn[i] == 'Q' ) {
                pm->boardCopy[m.iDest][m.jDest] = WHITE_QUEEN;
                pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
                break;
            } else if ( pgn[i] == 'N' ) {
                pm->boardCopy[m.iDest][m.jDest] = WHITE_KNIGHT;
                pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
                break;
            } else if ( pgn[i] == 'B' ) {
                pm->boardCopy[m.iDest][m.jDest] = WHITE_BISHOP;
                pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
                break;
            } else if ( pgn[i] == 'R' ) {
                pm->boardCopy[m.iDest][m.jDest] = WHITE_ROOK;
                pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
                break;
            }
        }
    } else if ( (m.isPromotion) && (m.srcPiece == BLACK_PAWN) && (m.iDest == SIZE-1) ) {
        for ( int i = 2 ; i < strlen(pgn) ; i++ ) {
            if ( pgn[i] == 'Q' ) {
                pm->boardCopy[m.iDest][m.jDest] = BLACK_QUEEN;
                pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
                break;
            } else if ( pgn[i] == 'N' ) {
                pm->boardCopy[m.iDest][m.jDest] = BLACK_KNIGHT;
                pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
                break;
            } else if ( pgn[i] == 'B' ) {
                pm->boardCopy[m.iDest][m.jDest] = BLACK_BISHOP;
                pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
                break;
            } else if ( pgn[i] == 'R' ) {
                pm->boardCopy[m.iDest][m.jDest] = BLACK_ROOK;
                pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
                break;
            }
        }
    }
}

/**************************************************************************************************
* Function name:        updateBoardCopy
* Input:                char board as 2D array, char PGN, Move struct and pointer to the struct.
* Output:               prints an error if source piece can't move to destination according to
                        canGo (according to pathBoard).
* Function Operation:   make the move on boardCopy in order to analyze it in the next functions.
**************************************************************************************************/
void updateBoardCopy(char board[][SIZE], char pgn[], Move m, Move* pm) {

    if ( (canGo(board, m)) && (m.isPromotion) && (m.srcPiece == WHITE_PAWN || m.srcPiece == BLACK_PAWN)
        && (m.iDest == 0 || m.iDest == SIZE-1) ) {
        promotion(board, pgn, m, pm);
        pm->isLegal = 1;
    } else if ( canGo(board, m) ) {
        pm->boardCopy[m.iDest][m.jDest] = m.srcPiece;
        pm->boardCopy[m.iSrc][m.jSrc] = EMPTY;
        pm->isLegal = 1;
    } else {
        pm->isLegal = 0;
    }

}

/**************************************************************************************************
* Function name:        checkRisk
* Input:                char board as 2D array (mainly to use with m.boardCopy)
                        char king (WHITE_KING or BLACK_KING)
                        int kingRow & int kingColumn (decided to enter it manually)
* Output:               1 - there is a threat on the relevant king (king color depends on char king)
                        0 - no threat to the relevant king
* Function Operation:   this function gets a filled board, king color and his location
                        on the board - all from calling function.

                        Afterwards it looks for threats in every possible direction:
                        * North:    Look for an opponent Queen or Rook
                        * NW:       Look for an opponent Queen, Bishop or Pawn for white king
                        * West:     Look for an opponent Queen or Rook
                        * SW:       Look for an opponent Queen, Bishop or Pawn for black king
                        * South:    Look for an opponent Queen or Rook
                        * SE:       Look for an opponent Queen, Bishop or Pawn for black king
                        * East:     Look for an opponent Queen or Rook
                        * NE:       Look for an opponent Queen, Bishop or Pawn for white king
                        * In each color,Knights get special relation in the code.

                        If the function finds a non-threatening game-piece on the path,
                        it will stop look beyond that point (because the king is safe from
                        this specific direction).
**************************************************************************************************/
int checkRisk(char boardCopy[][SIZE], char king, int kingRow, int kingColumn) {

    if ( king == WHITE_KING ) {
        // Look North
        for ( int i = kingRow-1 ; i >= 0 ; i-- ) {
            if ( ((boardCopy[i][kingColumn] == BLACK_QUEEN) || (boardCopy[i][kingColumn] == BLACK_ROOK))
                && (i >= 0) ) {
                return 1;
            } else if ( (boardCopy[i][kingColumn] == EMPTY) && ( i >= 0) ) {
                continue;
            } else {
                break;
            }
        }
        // Look North-East
        for ( int i = kingRow-1 , j = kingColumn+1 ; i >= 0 , j < SIZE ; i-- , j++ ) {
            if ( ((boardCopy[i][j] == BLACK_QUEEN) || (boardCopy[i][j] == BLACK_BISHOP)) && (i >= 0)
                && (j < SIZE) ) {
                return 1;
            } else if ( (boardCopy[i][j] == BLACK_PAWN) && (i == kingRow-1) && (i >= 0) && (j < SIZE) ) {
                return 1;
            } else if ( (boardCopy[i][j] == EMPTY) && (i >= 0) && (j < SIZE) ) {
                continue;
            } else {
                break;
            }
        }
        // `
        for ( int j = kingColumn+1 ; j < SIZE ; j++ ) {
            if ( ((boardCopy[kingRow][j] == BLACK_QUEEN) || (boardCopy[kingRow][j] == BLACK_ROOK)) && (j<SIZE) ) {
                return 1;
            } else if ( (boardCopy[kingRow][j] == EMPTY) && (j < SIZE) ) {
                continue;
            } else {
                break;
            }
        }
        // Look South-East
        for ( int i = kingRow+1 , j = kingColumn+1 ; i < SIZE , j < SIZE ; i++ , j++ ) {
            if ( ((boardCopy[i][j] == BLACK_QUEEN) || (boardCopy[i][j] == BLACK_BISHOP)) && (i < SIZE)
                && (j < SIZE) ) {
                return 1;
            } else if ( (boardCopy[i][j] == EMPTY) && (i < SIZE) && (j < SIZE) ) {
                continue;
            } else {
                break;
            }
        }
        // Look South
        for ( int i = kingRow+1 ; i < SIZE ; i++ ) {
            if ( ((boardCopy[i][kingColumn] == BLACK_QUEEN) || (boardCopy[i][kingColumn] == BLACK_ROOK))
                && (i < SIZE) ) {
                return 1;
            } else if ( (boardCopy[i][kingColumn] == EMPTY) && (i < SIZE) ) {
                continue;
            } else {
                break;
            }
        }
        // Look South-West
        for ( int i = kingRow+1 , j = kingColumn-1 ; i < SIZE , j >= 0 ; i++ , j-- ) {
            if ( ((boardCopy[i][j] == BLACK_QUEEN) || (boardCopy[i][j] == BLACK_BISHOP)) && (i < SIZE)
                && (j >= 0) ) {
                return 1;
            } else if ( (boardCopy[i][j] == EMPTY) && (i < SIZE) && (j >= 0) ) {
                continue;
            } else {
                break;
            }
        }
        // Look West
        for ( int j = kingColumn-1 ; j >= 0 ; j-- ) {
            if ( ((boardCopy[kingRow][j] == BLACK_QUEEN) || (boardCopy[kingRow][j] == BLACK_ROOK))
                && (j >= 0) ) {
                return 1;
            } else if ( (boardCopy[kingRow][j] == EMPTY) && (j >= 0) ) {
                continue;
            } else {
                break;
            }
        }
        // Look North-West
        for ( int i = kingRow-1 , j = kingColumn-1 ; i >= 0 , j >= 0 ; i-- , j-- ) {
            if ( ((boardCopy[i][j] == BLACK_QUEEN) || (boardCopy[i][j] == BLACK_BISHOP)) && (i >= 0) && (j>=0) ) {
                return 1;
            } else if ( (boardCopy[i][j] == BLACK_PAWN) && (i == kingRow-1) && (i >= 0) && (j >= 0) ) {
                return 1;
            } else if ( (boardCopy[i][j] == EMPTY) && (i >= 0) && (j >= 0) ) {
                continue;
            } else {
                break;
            }
        }
        // Look for Knights
        if ( (boardCopy[kingRow-2][kingColumn+1] == BLACK_KNIGHT) && (kingRow-2 >= 0) && (kingColumn+1 < SIZE) ) {
            return 1;
        } else if ( (boardCopy[kingRow-1][kingColumn+2] == BLACK_KNIGHT) && (kingRow-1 >= 0)
                   && (kingColumn+2 < SIZE) ) {
            return 1;
        } else if ( (boardCopy[kingRow+1][kingColumn+2] == BLACK_KNIGHT) && (kingRow+1 < SIZE)
                   && (kingColumn+2 < SIZE) ) {
            return 1;
        } else if ( (boardCopy[kingRow+2][kingColumn+1] == BLACK_KNIGHT) && (kingRow+2 < SIZE)
                   && (kingColumn+1 < SIZE) ) {
            return 1;
        } else if ( (boardCopy[kingRow+2][kingColumn-1] == BLACK_KNIGHT) && (kingRow+2 < SIZE)
                   && (kingColumn-1 >= 0) ) {
            return 1;
        } else if ( (boardCopy[kingRow+1][kingColumn-2] == BLACK_KNIGHT) && (kingRow+1 < SIZE)
                   && (kingColumn-2 >= 0) ) {
            return 1;
        } else if ( (boardCopy[kingRow-1][kingColumn-2] == BLACK_KNIGHT) && (kingRow-1 >= 0)
                   && (kingColumn-2 >= 0) ) {
            return 1;
        } else if ( (boardCopy[kingRow-2][kingColumn-1] == BLACK_KNIGHT) && (kingRow-2 >= 0)
                   && (kingColumn-1 >= 0) ) {
            return 1;
        }
        // If none of the conditions above returned 1, no threat on WHITE king, return 0.
        return 0;
    }
    else if ( king == BLACK_KING ) {
        // Look North
        for ( int i = kingRow-1 ; i >= 0 ; i-- ) {
            if ( ((boardCopy[i][kingColumn] == WHITE_QUEEN) || (boardCopy[i][kingColumn] == WHITE_ROOK))
                && (i >= 0) ) {
                return 1;
            } else if ( (boardCopy[i][kingColumn] == EMPTY) && (i >= 0) ) {
                continue;
            } else {
                break;
            }
        }
        // Look North-East
        for ( int i = kingRow-1 , j = kingColumn+1 ; i >= 0 , j < SIZE ; i-- , j++ ) {
            if ( ((boardCopy[i][j] == WHITE_QUEEN) || (boardCopy[i][j] == WHITE_BISHOP)) && (i >= 0)
                && (j < SIZE) ) {
                return 1;
            } else if ( (boardCopy[i][j] == EMPTY) && (i >= 0) && (j < SIZE) ) {
                continue;
            } else {
                break;
            }
        }
        // Look East
        for ( int j = kingColumn+1 ; j < SIZE ; j++ ) {
            if ( ((boardCopy[kingRow][j] == WHITE_QUEEN) || (boardCopy[kingRow][j] == WHITE_ROOK)) && (j<SIZE) ) {
                return 1;
            } else if ( (boardCopy[kingRow][j] == EMPTY) && (j < SIZE) ) {
                continue;
            } else {
                break;
            }
        }
        // Look South-East
        for ( int i = kingRow+1 , j = kingColumn+1 ; i < SIZE , j < SIZE ; i++ , j++ ) {
            if ( ((boardCopy[i][j] == WHITE_QUEEN) || (boardCopy[i][j] == WHITE_BISHOP)) && (i < SIZE)
                && (j < SIZE) ) {
                return 1;
            } else if ( (boardCopy[i][j] == WHITE_PAWN) && (i == kingRow+1) && (i < SIZE) && (j < SIZE) ) {
                return 1;
            }  else if ( (boardCopy[i][j] == EMPTY) && (i < SIZE) && (j < SIZE) ) {
                continue;
            } else {
                break;
            }
        }
        // Look South
        for ( int i = kingRow+1 ; i < SIZE ; i++ ) {
            if ( ((boardCopy[i][kingColumn] == WHITE_QUEEN) || (boardCopy[i][kingColumn] == WHITE_ROOK))
                && (i < SIZE) ) {
                return 1;
            } else if ( (boardCopy[i][kingColumn] == EMPTY) && (i < SIZE) ) {
                continue;
            } else {
                break;
            }
        }
        // Look South-West
        for ( int i = kingRow+1 , j = kingColumn-1 ; i < SIZE , j >= 0 ; i++ , j-- ) {
            if ( ((boardCopy[i][j] == WHITE_QUEEN) || (boardCopy[i][j] == WHITE_BISHOP)) && (i < SIZE)
                && (j >= 0) ) {
                return 1;
            } else if ( (boardCopy[i][j] == WHITE_PAWN) && (i == kingRow+1) && (i < SIZE) && (j >= 0) ) {
                return 1;
            } else if ( (boardCopy[i][j] == EMPTY) && (i < SIZE) && (j >= 0) ) {
                continue;
            } else {
                break;
            }
        }
        // Look West
        for ( int j = kingColumn-1 ; j >= 0 ; j-- ) {
            if ( ((boardCopy[kingRow][j] == WHITE_QUEEN) || (boardCopy[kingRow][j] == WHITE_ROOK))
                && (j >= 0) ) {
                return 1;
            } else if ( (boardCopy[kingRow][j] == EMPTY) && (j >= 0) ) {
                continue;
            } else {
                break;
            }
        }
        // Look North-West
        for ( int i = kingRow-1 , j = kingColumn-1 ; i >= 0 , j >= 0 ; i-- , j-- ) {
            if ( ((boardCopy[i][j] == WHITE_QUEEN) || (boardCopy[i][j] == WHITE_BISHOP)) && (i >= 0) && (j>=0) ) {
                return 1;
            } else if ( (boardCopy[i][j] == EMPTY) && (i >= 0) && (j >= 0) ) {
                continue;
            } else {
                break;
            }
        }
        // Look for Knights
        if ( (boardCopy[kingRow-2][kingColumn+1] == WHITE_KNIGHT) && (kingRow-2 >= 0)
            && (kingColumn+1 < SIZE) ) {
            return 1;
        } else if ( (boardCopy[kingRow-1][kingColumn+2] == WHITE_KNIGHT) && (kingRow-1 >= 0)
                   && (kingColumn+2 < SIZE) ) {
            return 1;
        } else if ( (boardCopy[kingRow+1][kingColumn+2] == WHITE_KNIGHT) && (kingRow+1 < SIZE)
                   && (kingColumn+2 < SIZE) ) {
            return 1;
        } else if ( (boardCopy[kingRow+2][kingColumn+1] == WHITE_KNIGHT) && (kingRow+2 < SIZE)
                   && (kingColumn+1 < SIZE) ) {
            return 1;
        } else if ( (boardCopy[kingRow+2][kingColumn-1] == WHITE_KNIGHT) && (kingRow+2 < SIZE)
                   && (kingColumn-1 >= 0) ) {
            return 1;
        } else if ( (boardCopy[kingRow+1][kingColumn-2] == WHITE_KNIGHT) && (kingRow+1 < SIZE)
                   && (kingColumn-2 >= 0) ) {
            return 1;
        } else if ( (boardCopy[kingRow-1][kingColumn-2] == WHITE_KNIGHT) && (kingRow-1 >= 0)
                   && (kingColumn-2 >= 0) ) {
            return 1;
        } else if ( (boardCopy[kingRow-2][kingColumn-1] == WHITE_KNIGHT) && (kingRow-2 >= 0)
                   && (kingColumn-1 >= 0) ) {
            return 1;
        }
        // If none of the conditions above returned 1, no threat on BLACK king, return 0.
        return 0;
    }

}

/**************************************************************************************************
* Function name:        checkMate
* Input:                the Turn (int) and the struct m (Move).
* Output:               1 - valid, 0 - not-valid.
* Function Operation:   determine whether the use of Check or Mate is valid. As we instructed to
                        relate to Check and Mate the same, this function define "marked PGN" as a
                        PGN with "+" char or "#" char. If the given PGN is "marked", the function
                        will verify that there is actual threat on the opponent king (if no
                        threat, return 0). if there is an actual threat but the given PGN is
                        "un-marked", the function will return 0. For valid situation the function
                        will return 1.
**************************************************************************************************/
int checkMate(int isWhiteTurn, Move m) {
    // Note: we've been instructed to relate to Check and Mate the same.
    // Initialize kings coordinates to -1 in order to differentiate between coordinate (0,0) error in finding them.
    int whiteKingRow = -1, blackKingRow = -1, whiteKingColumn = -1, blackKingColumn = -1;
    // Find kings coordinates
    for ( int i = 0 ; i < SIZE ; i++ ) {
        for ( int j = 0 ; j < SIZE ; j++ ) {
            if ( m.boardCopy[i][j] == WHITE_KING ) {
                whiteKingRow = i;
                whiteKingColumn = j;
            } else if ( m.boardCopy[i][j] == BLACK_KING ) {
                blackKingRow = i;
                blackKingColumn = j;
            }
        }
    }
    // Look for invalid cases. If there aren't, return 1 (valid).
    if ( m.isCheck || m.isMate ) {
        if ( isWhiteTurn && checkRisk(m.boardCopy, BLACK_KING, blackKingRow, blackKingColumn) != 1 ) {
            return 0;
        } else if ( !isWhiteTurn && checkRisk(m.boardCopy, WHITE_KING, whiteKingRow, whiteKingColumn) != 1 ) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if ( isWhiteTurn && checkRisk(m.boardCopy, BLACK_KING, blackKingRow, blackKingColumn) == 1 ) {
            return 0;
        } else if ( !isWhiteTurn && checkRisk(m.boardCopy, WHITE_KING, whiteKingRow, whiteKingColumn) == 1 ) {
            return 0;
        } else {
            return 1;
        }
    }
}

/**************************************************************************************************
* Function name:        capture
* Input:                char board as 2D array, the Turn and Move m (struct).
* Output:               1 - valid, 0 - not-valid.
* Function Operation:   determine whether the use of Capture is valid. If there is a capture sign
                        in the PGN and there is no opponent piece in destination or if there is no
                        capture sign in PGN the there is an opponent piece in destination,
                        return 0. else, return 1.
**************************************************************************************************/
int capture(char board[][SIZE],int isWhiteTurn , Move m) {

    if ( (isWhiteTurn) && (m.isCapture) && (checkCell(board, m.iDest, m.jDest) != IS_BLACK) ) {
        return 0;
    } else if ( (!isWhiteTurn) && (m.isCapture) && (checkCell(board, m.iDest, m.jDest) != IS_WHITE) ) {
        return 0;
    } else if ( (isWhiteTurn) && (!m.isCapture) && (checkCell(board, m.iDest, m.jDest) == IS_BLACK) ) {
        return 0;
    } else if ( (!isWhiteTurn) && (!m.isCapture) && (checkCell(board, m.iDest, m.jDest) == IS_WHITE) ) {
        return 0;
    } else {
        return 1;
    }

}

/**************************************************************************************************
* Function name:        isKingSafe
* Input:                char board as 2D array, the Turn and Move m (struct).
* Output:               1 - friendly king is safe, 0 - he isn't.
* Function Operation:   after making the move on the boardCopy, function called to determine
                        whether the friendly king is safe from opponent characters if he is safe,
                        the function will return 1. If not, it will return 0.
**************************************************************************************************/
int isKingSafe(char board[][SIZE], int isWhiteTurn, Move m) {

    // Initialize kings coordinates to -1 in order to differentiate between coordinate (0,0) error in finding them.
    int whiteKingRow = -1, blackKingRow = -1, whiteKingColumn = -1, blackKingColumn = -1;
    // Find kings coordinates
    for ( int i = 0 ; i < SIZE ; i++ ) {
        for ( int j = 0 ; j < SIZE ; j++ ) {
            if ( m.boardCopy[i][j] == WHITE_KING ) {
                whiteKingRow = i;
                whiteKingColumn = j;
                break;
            } else if ( m.boardCopy[i][j] == BLACK_KING ) {
                blackKingRow = i;
                blackKingColumn = j;
                break;
            }
        }
    }

    if ( isWhiteTurn && checkRisk(m.boardCopy, WHITE_KING, whiteKingRow, whiteKingColumn) ) {
        return 0;
    } else if ( !isWhiteTurn && checkRisk(m.boardCopy, BLACK_KING, blackKingRow, blackKingColumn) ) {
        return 0;
    } else {
        return 1;
    }

}

/**************************************************************************************************
* Function name:        isLegalMove
* Input:                the Turn (int) and the struct m (Move).
* Output:               1 - legal, 0 - non-legal.
* Function Operation:   this function determine whether the move that is being done on the
                        boardCopy is legal or not, according to 4 parameters:
                        1) m.isLegal = If the destination was not filled with friendly character
                        2) checkMate = If the use of check or mate symbols is legal
                        3) capture = If the use of capture sign is legal
                        4) isKingSafe = If the player does not expose his king to a threat
**************************************************************************************************/
int isLegalMove(char board[][SIZE], int isWhiteTurn, Move m) {

    if ( !checkMate(isWhiteTurn, m) || !capture(board, isWhiteTurn, m)
            || !m.isLegal || !isKingSafe(board, isWhiteTurn, m) ) {
        return 0;
    } else {
        return 1;

    }


}

/**************************************************************************************************
* Function name:        makeMove
* Input:                char board[][SIZE], char pgn[], int isWhiteTurn
* Output:               None
* Function Operation:   this function is objective 3 of the assignment. It is called by the main
                        function and it calls to other functions in ass4.c file by a specific
                        sequence. If the move (according to the given PGN) is valid, the function
                        will feed board[][] with boardCopy[][] values and return 1.Else, return 0.
**************************************************************************************************/
int makeMove(char board[][SIZE], char pgn[], int isWhiteTurn) {

    Move m;
    Move* pm = &m;

    resetStruct(pm);

    initSrcPiece(pgn, isWhiteTurn, pm);
    initSpecAct(pgn, pm);
    initDest(pgn, pm);
    initSrc(board, pgn, isWhiteTurn, pm, m);
    initPathBoard(board, m, pm);
    initBoardCopy(board, pm);
    updatePathBoard(board, m, pm);
    updateBoardCopy(board, pgn, m, pm);

    if ( isLegalMove(board, isWhiteTurn, m) ) {
        for ( int i = 0 ; i < SIZE ; i++ ) {
            for ( int j = 0 ; j < SIZE ; j++ ) {
                board[i][j] = m.boardCopy[i][j];
            }
        }
        return 1;
    } else {
        return 0;
    }

}



