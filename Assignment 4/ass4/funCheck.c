#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "ass4.h"

// Move logical representation
typedef struct {
    char srcPiece, srcRow, srcCol, destPiece, destRow, destCol;
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

int toDigit(char c) {
    assert('0' <= c && c <= '9');
    return c - '0';
}

int toColIndex(char c) {
    assert('a' <= c && c <= 'z');
    return c - 'a';
}

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

void printSpacers() {
    printf("* -");
    for (int i = 0; i < SIZE; i++) {
        printf("--");
    }
    printf(" *\n");
}

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

void createBoard(char board[][SIZE], char fen[]) {

    int fenLoc = 0, i = 0, j = 0, num = 0;
    while ( fenLoc < SIZE*SIZE ) {
        if ( isdigit(fen[fenLoc])) {
            num = toDigit(fen[fenLoc]);
            for ( int k = 0 ; k < num ; k++ ) {
                board[i][j] = ' ';
                j++;
            }
        } else if ( fen[fenLoc] == SEP[0] ) {
            i++;
            j = 0;
        } else {
            board[i][j] = fen[fenLoc];
            j++;
        }
        fenLoc++;
    }
}

void printBoard(char board[][SIZE]) {

    printColumns();
    printSpacers();
    int rowIdx = SIZE, i = 0, j = 0;
    char rowFromBoard[SIZE];
    while ( rowIdx > 0 ) {
        for ( j = 0 ; j < SIZE ; j++) {
            rowFromBoard[j] = board[i][j];
        }
        printRow(rowFromBoard, rowIdx--);
        i++;
    }
    printSpacers();
    printColumns();

}

void character(char pgn[]) {

    Move m;
    Move* pm = &m;

    for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
        if ( pgn[0] == 'K') {
            pm->srcPiece = KING;
        } else if ( pgn[0] == 'Q') {
            pm->srcPiece = QUEEN;
        } else if ( pgn[0] == 'B') {
            pm->srcPiece = BISHOP;
        } else if ( pgn[0] == 'N') {
            pm->srcPiece = KNIGHT;
        } else if ( pgn[0] == 'R') {
            pm->srcPiece = ROOK;
        } else {
            pm->srcPiece = PAWN;
        }
    }
}

void movementRules(char srcPiece, int iDest, int jDest, int iSrc, int jSrc, int isWhiteTurn) {

    Move m;

    int rowChange = abs(m.iDest-m.iSrc);
    int colChange = abs(m.jDest-m.jSrc);

    if (rowChange == 0 && colChange == 0) {
        return 0;
    } else {
        switch (m.srcPiece) {

            case 'KING':    if ( rowChange <= 1 && colChange <= 1 ) {
                                return 1;
                            } else {
                                return 0;
                            }
                            break;

            case 'QUEEN':   if ( (rowChange == colChange) || (m.iDest == m.iSrc) || (m.jDest == m.jSrc) ) {
                                return 1;
                            } else {
                                return 0;
                            }
                            break;

            case 'BISHOP':  if ( rowChange == colChange ) {
                                return 1;
                            } else {
                                return 0;
                            }
                            break;

            case 'ROOK':    if ( (m.iDest == m.iSrc) || (m.jDest == m.jSrc ) ) {
                                return 1;
                            } else {
                                return 0;
                            }
                            break;

            case 'KNIGHT':  if ( (rowChange + colChange == 3) && (rowChange != 0) && (colChange != 0) ) {
                                return 1;
                            } else {
                                return 0;
                            }
                            break;

            case 'PAWN':    if ( m.isCapture == 0) {
                                if ( m.jDest != m.jSrc ) {
                                    return 0;
                                } else {
                                    if ( isWhiteTurn == 1 ) {
                                        if ( m.iSrc-m.iDest == 1 ) {
                                            return 1;
                                        } else if ( (m.iSrc == SIZE-2) && (m.iDest == SIZE-4) ) {
                                            return 1;
                                        } else {
                                            return 0;
                                        }
                                    } else if ( isWhiteTurn == 0 ) {
                                        if ( m.iDest-m.iSrc == 1 ) {
                                            return 1;
                                        } else if ( (m.iSrc == 1) && (m.iDest == 3) ) {
                                            return 1;
                                        } else {
                                            return 0;
                                        }
                                    } else {
                                        return 0;
                                    }
                                }

                            } else { // isCapture == 1
                                if ( isWhiteTurn == 1 ) {
                                    if ( (colChange <= 1) && ( m.iSrc-m.iDest == 1 ) ) {
                                        return 1;
                                    } else if ( (m.iSrc == SIZE-2) && (m.iDest == SIZE-4) ) {
                                        return 1;
                                    } else {
                                        return 0;
                                    }
                                } else if ( isWhiteTurn == 0 ) {
                                    if ( (colChange <= 1) && (m.iDest-m.iSrc == 1) ) {
                                        return 1;
                                    } else if ( (m.iSrc == 1) && (m.iDest == 3) ) {
                                        return 1;
                                    } else {
                                        return 0;
                                    }
                                } else {
                                    return 0;
                                }
                            }
                            break;

        }

    }

}

void movementVector(char pgn[]) {

    Move m;
    Move* pm = &m;

    int lowCaseCounter = 0, digitCounter = 0;
    // A loop to find coordinates type
    for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
        if ( islower(pgn[i]) && pgn[i] != 'x' ) {
            lowCaseCounter++;
        } else if ( isdigit(pgn[i]) ) {
            digitCounter++;
        }
    }
    // Type 1: Only destination given
    if ( lowCaseCounter == 1 && digitCounter == 1) {
        for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
            if ( islower(pgn[i]) ) {
                pm->jDest = toColIndex(pgn[i]);
            } else if ( isdigit(pgn[i]) ) {
                pm->iDest = toDigit(pgn[i]);
            }
        }
    // Type 2: Destination and j-Src given
    } else if ( lowCaseCounter == 2 ) {
        int readCount = 0;
        for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
            if ( islower(pgn[i]) && readCount == 0 ) {
                pm->jSrc = toColIndex(pgn[i]);
                readCount++;
            } else if ( islower(pgn[i]) && readCount > 0 ) {
                pm->jDest = toColIndex(pgn[i]);
            } else if ( isdigit(pgn[i]) ) {
                pm->iDest = toDigit(pgn[i]);
            }
        }
    // Type 3: Destination and i-Src given
    } else if ( digitCounter == 2 ) {
        int readCount = 0;
        for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
            if ( islower(pgn[i]) ) {
                pm->jDest = toColIndex(pgn[i]);
            } else if ( isdigit(pgn[i]) && readCount == 0 ) {
                pm->iSrc = toColIndex(pgn[i]);
                readCount++;
            } else if ( isdigit(pgn[i]) && readCount > 0) {
                pm->iDest = toDigit(pgn[i]);
            }
        }

    }

}

void isSpecial(char pgn[]) {

    Move m;
    Move* pm = &m;

    for ( int i = 0 ; i < strlen(pgn) ; i++ ) {
        if ( pgn[i] == '+' ) {
            pm->isCheck = 1;
        } else if ( pgn[i] == '#' ) {
            pm->isMate = 1;
        } else if ( pgn[i] == 'x' ) {
            pm->isCapture = 1;
        } else if ( pgn[i] == '=' ) {
            pm->isPromotion = 1;
        } else {
            return 0;
        }
    }
}

void occupation(char board[][SIZE], int iDest, int jDest) {

    Move m;

    if ( isupper(board[m.iDest][m.jDest]) ) {
        return 1; // For white
    } else if ( islower(board[m.iDest][m.jDest]) ) {
        return 2; // For black
    } else if ( board[m.iDest][m.jDest] == ' ' ) {
        return 0; // For empty
    }
}

void makeMove(char board[][SIZE], char pgn[], int isWhiteTurn) {

    Move m;
    Move* pm = &m;

    int possiblePieces = 0;

    character(pgn);
    movementVector(pgn);

    printf("I_DEST: %d | J_DEST: %d", m.iDest, m.jDest);
/*
    if ( isWhiteTurn == 1 ) {
        if ( occupation(board, m.iDest, m.jDest) == 1 ) {
            return 0;
        }
        for ( int i = 0 ; i < SIZE ; i++ ) {
            for ( int j = 0 ; j < SIZE ; j++ ) {
                if ( movementRules(m.srcPiece, m.iDest, m.jDest, i, j, isWhiteTurn) ) {
                    possiblePieces++;
                }
            }
        }
        if ( possiblePieces == 0 ) {
            return 0;
        } else if ( possiblePieces == 1 ) {
            for ( int i = 0 ; i < SIZE ; i++ ) {
                for ( int j = 0 ; j < SIZE ; j++ ) {
                    if ( movementRules(m.srcPiece, m.iDest, m.jDest, i, j, isWhiteTurn) ) {
                        pm->iSrc = i;
                        pm->jSrc = j;
                    } else {
                        return 0;
                    }
                }
            }
        } else {
            for ( int i = 0 ; i < SIZE ; i++ ) {
                for ( int j = 0 ; j < SIZE ; j++ ) {
                    if ( movementRules(m.srcPiece, m.iDest, m.jDest, i, j, isWhiteTurn) ) {
                        if ( (i == m.iSrc) || (j == m.jSrc) ) {
                            pm->iSrc = i;
                            pm->jSrc = j;
                        } else {
                            return 0;
                        }
                    } else {
                        return 0;
                    }
                }
            }
        }
        pm->isLegal = 1;

    } else if ( isWhiteTurn == 0 ) {
        if ( occupation(board) == 2 ) {
            return 0;
        }
        for ( int i = 0 ; i < SIZE ; i++ ) {
            for ( int j = 0 ; j < SIZE ; j++ ) {
                if ( movementRules(m.srcPiece, m.iDest, m.jDest, i, j, isWhiteTurn) ) {
                    possiblePieces++;
                }
            }
        }
        if ( possiblePieces == 0 ) {
            return 0;
        } else if ( possiblePieces == 1 ) {
            for ( int i = 0 ; i < SIZE ; i++ ) {
                for ( int j = 0 ; j < SIZE ; j++ ) {
                    if ( movementRules(m.srcPiece, m.iDest, m.jDest, i, j, isWhiteTurn) ) {
                        pm->iSrc = i;
                        pm->jSrc = j;
                    } else {
                        return 0;
                    }
                }
            }
        } else {
            for ( int i = 0 ; i < SIZE ; i++ ) {
                for ( int j = 0 ; j < SIZE ; j++ ) {
                    if ( movementRules(m.srcPiece, m.iDest, m.jDest, i, j, isWhiteTurn) ) {
                        if ( (i == m.iSrc) || (j == m.jSrc) ) {
                            pm->iSrc = i;
                            pm->jSrc = j;
                        } else {
                            return 0;
                        }
                    } else {
                        return 0;
                    }
                }
            }
        }
        pm->isLegal = 1;
    } else {
        return 0;
    }

    board[m.iDest][m.jDest] = m.srcPiece;
    board[m.iSrc][m.jSrc] = ' ';
*/
}
