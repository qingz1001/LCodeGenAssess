#include <stdio.h>
#include <stdlib.h>

#define N 4

void printSolution(int steps, int** moves) {
    printf("%d\n", steps);
    for (int i = 0; i < steps; i++) {
        printf("%d%d%d%d\n", moves[i][0], moves[i][1], moves[i][2], moves[i][3]);
    }
}

int main() {
    int initial[N][N];
    int target[N][N];

    // Read initial state
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &initial[i][j]);
        }
    }

    // Read target state
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &target[i][j]);
        }
    }

    // Placeholder for the solution logic
    // This is a simplified version and does not implement the actual game logic
    int steps = 0;
    int** moves = NULL;

    // Example solution: swap adjacent cells until the target state is reached
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] != target[i][j]) {
                // Swap with the next cell
                if (i + 1 < N && initial[i + 1][j] == target[i][j]) {
                    initial[i][j] ^= 1;
                    initial[i + 1][j] ^= 1;
                    steps++;
                    moves = realloc(moves, steps * sizeof(int*));
                    moves[steps - 1] = malloc(4 * sizeof(int));
                    moves[steps - 1][0] = i;
                    moves[steps - 1][1] = j;
                    moves[steps - 1][2] = i + 1;
                    moves[steps - 1][3] = j;
                } else if (j + 1 < N && initial[i][j + 1] == target[i][j]) {
                    initial[i][j] ^= 1;
                    initial[i][j + 1] ^= 1;
                    steps++;
                    moves = realloc(moves, steps * sizeof(int*));
                    moves[steps - 1] = malloc(4 * sizeof(int));
                    moves[steps - 1][0] = i;
                    moves[steps - 1][1] = j;
                    moves[steps - 1][2] = i;
                    moves[steps - 1][3] = j + 1;
                }
            }
        }
    }

    // Print the solution
    printSolution(steps, moves);

    // Free allocated memory
    for (int i = 0; i < steps; i++) {
        free(moves[i]);
    }
    free(moves);

    return 0;
}