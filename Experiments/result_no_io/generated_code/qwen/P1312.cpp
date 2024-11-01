#include <stdio.h>
#include <stdlib.h>

#define ROWS 7
#define COLS 5

void printBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void movePiece(int board[ROWS][COLS], int x, int y, int g) {
    if (g == 1) {
        while (y + 1 < COLS && board[x][y + 1] != 0) {
            int temp = board[x][y];
            board[x][y] = board[x][y + 1];
            board[x][y + 1] = temp;
            y++;
        }
    } else {
        while (y > 0 && board[x][y - 1] != 0) {
            int temp = board[x][y];
            board[x][y] = board[x][y - 1];
            board[x][y - 1] = temp;
            y--;
        }
    }
}

int checkAndRemove(int board[ROWS][COLS]) {
    int removed = 0;
    // Check rows
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 3; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]) {
                for (int k = j; k <= j + 2; k++) {
                    board[i][k] = 0;
                }
                removed = 1;
            }
        }
    }
    // Check columns
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i <= ROWS - 3; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j]) {
                for (int k = i; k <= i + 2; k++) {
                    board[k][j] = 0;
                }
                removed = 1;
            }
        }
    }
    return removed;
}

int dropPieces(int board[ROWS][COLS]) {
    int moved = 0;
    for (int j = 0; j < COLS; j++) {
        int emptyRow = ROWS - 1;
        for (int i = ROWS - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (i != emptyRow) {
                    board[emptyRow--][j] = board[i][j];
                    board[i][j] = 0;
                    moved = 1;
                }
            } else {
                emptyRow--;
            }
        }
    }
    return moved;
}

int main() {
    int n;
    scanf("%d", &n);
    int board[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 0) break;
        }
    }

    for (int step = 0; step < n; step++) {
        int foundMove = 0;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != 0) {
                    for (int g = -1; g <= 1; g += 2) {
                        int original = board[i][j];
                        movePiece(board, i, j, g);
                        if (checkAndRemove(board)) {
                            foundMove = 1;
                            printf("%d %d %d\n", i, j, g);
                            if (dropPieces(board)) {
                                i = -1; j = -1;
                            }
                            break;
                        }
                        board[i][j] = original;
                    }
                    if (foundMove) break;
                }
            }
            if (foundMove) break;
        }
        if (!foundMove) {
            printf("-1\n");
            return 0;
        }
    }

    return 0;
}