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
    if (g == 1 && y + 1 < COLS && board[x][y + 1] != 0) {
        // Swap pieces
        int temp = board[x][y];
        board[x][y] = board[x][y + 1];
        board[x][y + 1] = temp;
    } else if (g == -1 && y > 0 && board[x][y - 1] != 0) {
        // Swap pieces
        int temp = board[x][y];
        board[x][y] = board[x][y - 1];
        board[x][y - 1] = temp;
    } else {
        // Drop piece
        while (x > 0 && board[x - 1][y] == 0) {
            board[x][y] = board[x - 1][y];
            board[--x][y] = 0;
        }
    }
}

int checkAndEliminate(int board[ROWS][COLS]) {
    int eliminated = 0;
    // Check rows
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 3; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]) {
                for (int k = j; k <= j + 2; k++) {
                    board[i][k] = 0;
                    eliminated++;
                }
            }
        }
    }
    // Check columns
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i <= ROWS - 3; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j]) {
                for (int k = i; k <= i + 2; k++) {
                    board[k][j] = 0;
                    eliminated++;
                }
            }
        }
    }
    return eliminated;
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
        int minMoves = 999999;
        int bestMoveX = -1, bestMoveY = -1, bestMoveG = -1;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != 0) {
                    for (int g = -1; g <= 1; g += 2) {
                        int tempBoard[ROWS][COLS];
                        memcpy(tempBoard, board, sizeof(board));
                        movePiece(tempBoard, i, j, g);
                        int moves = checkAndEliminate(tempBoard);
                        if (moves < minMoves) {
                            minMoves = moves;
                            bestMoveX = i;
                            bestMoveY = j;
                            bestMoveG = g;
                        }
                    }
                }
            }
        }

        if (bestMoveX == -1) {
            printf("-1\n");
            return 0;
        }

        movePiece(board, bestMoveX, bestMoveY, bestMoveG);
        printf("%d %d %d\n", bestMoveX, bestMoveY, bestMoveG);
    }

    return 0;
}