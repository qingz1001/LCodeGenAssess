#include <stdio.h>

// Function to perform left shift on the board
void leftShift(int board[4][4], int score) {
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (board[i][j] == 0) continue;
            for (k = j + 1; k < 4; k++) {
                if (board[i][k] == 0) continue;
                if (board[i][j] == board[i][k]) {
                    board[i][j] *= 2;
                    board[i][k] = 0;
                    score += board[i][j];
                    break;
                } else {
                    break;
                }
            }
        }
    }
}

// Function to check if the board is full
int isBoardFull(int board[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (board[i][j] == 0) return 0;
        }
    }
    return 1;
}

// Function to simulate the game and return the score
int simulateGame() {
    int board[4][4] = {0};
    int score = 0;
    int i, j, k;
    // Initial two moves by player C
    for (k = 0; k < 2; k++) {
        int r, c;
        do {
            r = rand() % 4;
            c = rand() % 4;
        } while (board[r][c] != 0);
        board[r][c] = rand() % 2 + 2;
    }

    // Game loop
    int player = 1; // 1 for M, 0 for C
    while (!isBoardFull(board)) {
        if (player == 1) { // Player M's turn
            // Perform left shift
            leftShift(board, score);
            player = 0;
        } else { // Player C's turn
            // Place a new number
            int r, c;
            do {
                r = rand() % 4;
                c = rand() % 4;
            } while (board[r][c] != 0);
            board[r][c] = rand() % 2 + 2;
            player = 1;
        }
    }
    return score;
}

int main() {
    int numTrials = 1000000;
    int totalScore = 0;
    int i;
    for (i = 0; i < numTrials; i++) {
        totalScore += simulateGame();
    }
    printf("Average score after %d trials: %d\n", numTrials, totalScore / numTrials);
    return 0;
}