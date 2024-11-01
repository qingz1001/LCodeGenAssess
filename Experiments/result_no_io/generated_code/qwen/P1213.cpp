#include <stdio.h>
#include <stdlib.h>

#define N 9

int moves[N][4] = {
    {0, 1, 3, 4},
    {0, 1, 2, 3},
    {1, 2, 3, 5, 6},
    {0, 3, 6, 7},
    {1, 3, 4, 5, 7, 8},
    {2, 5, 6, 8},
    {3, 4, 7, 8},
    {6, 7, 8},
    {7, 8}
};

void flip(int *clocks, int move) {
    for (int i = 0; i < moves[move - 1][i]; i++) {
        clocks[moves[move - 1][i]] = (clocks[moves[move - 1][i]] + 9) % 12;
    }
}

int main() {
    int clocks[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &clocks[i]);
    }

    int min_moves = INT_MAX;
    int best_sequence[N];

    // Try all permutations of moves
    do {
        int current_clocks[N];
        memcpy(current_clocks, clocks, sizeof(clocks));
        int sequence_length = 0;

        for (int i = 0; i < N; i++) {
            if (current_clocks[i] != 0) {
                flip(current_clocks, moves[i][0]);
                sequence_length++;
            }
        }

        if (sequence_length < min_moves) {
            min_moves = sequence_length;
            memcpy(best_sequence, moves, sizeof(moves));
        }
    } while (next_permutation(moves, moves + N));

    printf("%d ", best_sequence[0]);
    for (int i = 1; i < min_moves; i++) {
        printf("%d ", best_sequence[i]);
    }
    printf("\n");

    return 0;
}