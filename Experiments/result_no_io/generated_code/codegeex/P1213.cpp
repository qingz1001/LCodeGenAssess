#include <stdio.h>

int main() {
    int clocks[9];
    int i, j, k, l, m, n, count, min_moves = 100, solution[100];
    int moves[9][4] = {
        {0, 1, 3, 4},  // Move 1 affects clocks A, B, D, E
        {0, 1, 2},     // Move 2 affects clocks A, B, C
        {1, 2, 4, 5},  // Move 3 affects clocks B, C, E, F
        {0, 3, 6},     // Move 4 affects clocks A, D, G
        {1, 3, 4, 5, 7}, // Move 5 affects clocks B, D, E, F, H
        {2, 5, 8},     // Move 6 affects clocks C, F, I
        {3, 4, 6, 7},  // Move 7 affects clocks D, E, G, H
        {6, 7, 8},     // Move 8 affects clocks G, H, I
        {4, 5, 7, 8}   // Move 9 affects clocks E, F, H, I
    };

    // Read the initial clock times (1 for 12 o'clock, 2 for 3 o'clock, etc.)
    for (i = 0; i < 9; i++) {
        scanf("%d", &clocks[i]);
    }

    // Try all possible combinations of moves
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                for (l = 0; l < 4; l++) {
                    for (m = 0; m < 4; m++) {
                        for (n = 0; n < 4; n++) {
                            for (count = 0; count < 9; count++) {
                                solution[count] = 0;
                            }

                            solution[0] = i + 1;
                            solution[1] = j + 1;
                            solution[2] = k + 1;
                            solution[3] = l + 1;
                            solution[4] = m + 1;
                            solution[5] = n + 1;

                            int temp_clocks[9];
                            for (count = 0; count < 9; count++) {
                                temp_clocks[count] = clocks[count];
                            }

                            // Apply the moves
                            for (count = 0; count < 9; count++) {
                                int move = solution[count];
                                for (int a = 0; a < 4; a++) {
                                    temp_clocks[moves[count][a]] = (temp_clocks[moves[count][a]] + move) % 4;
                                }
                            }

                            // Check if all clocks are at 12 o'clock
                            int all_twelve = 1;
                            for (count = 0; count < 9; count++) {
                                if (temp_clocks[count] != 0) {
                                    all_twelve = 0;
                                    break;
                                }
                            }

                            // If all clocks are at 12 o'clock and fewer moves, update the solution
                            if (all_twelve && (i + j + k + l + m + n < min_moves)) {
                                min_moves = i + j + k + l + m + n;
                                for (count = 0; count < 9; count++) {
                                    printf("%d ", solution[count]);
                                }
                                printf("\n");
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}