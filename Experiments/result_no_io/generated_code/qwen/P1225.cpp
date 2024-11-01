#include <stdio.h>
#include <stdlib.h>

#define N 4

int board[N][N];
int target[N][N];

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Read initial and target boards
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &target[i][j]);
        }
    }

    // Compare the two boards to find the minimum number of moves
    int moves = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != target[i][j]) {
                // Find a matching piece in the target board
                int found = 0;
                for (int x = 0; x < N && !found; x++) {
                    for (int y = 0; y < N && !found; y++) {
                        if (x != i || y != j) {
                            if (board[x][y] == target[i][j]) {
                                // Swap the pieces
                                int temp = board[i][j];
                                board[i][j] = board[x][y];
                                board[x][y] = temp;

                                // Print the move
                                printf("%d %d %d %d\n", i, j, x, y);

                                // Increment the move count
                                moves++;

                                // Update the board
                                board[i][j] = target[i][j];
                                board[x][y] = temp;

                                found = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    // Output the number of moves
    printf("%d\n", moves);

    return 0;
}