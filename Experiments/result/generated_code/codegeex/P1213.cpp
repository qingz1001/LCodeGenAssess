#include <stdio.h>

int main() {
    int clocks[9];
    int moves[9] = {1, 1, 1, 1, 2, 2, 2, 2, 3};
    int affected[9][7] = {
        {0, 1, 3, -1, -1, -1, -1}, // Move 1 affects A, B, D, E
        {0, 1, 2, -1, -1, -1, -1}, // Move 2 affects A, B, C
        {1, 2, 4, -1, -1, -1, -1}, // Move 3 affects B, C, E, F
        {0, 3, 6, -1, -1, -1, -1}, // Move 4 affects A, D, G
        {0, 1, 3, 5, 7, -1, -1},   // Move 5 affects A, B, D, E, F, H
        {2, 4, 6, -1, -1, -1, -1}, // Move 6 affects C, E, G, I
        {3, 5, 7, -1, -1, -1, -1}, // Move 7 affects D, E, G, H
        {6, 7, 8, -1, -1, -1, -1}, // Move 8 affects G, H, I
        {4, 5, 8, -1, -1, -1, -1}  // Move 9 affects E, F, H, I
    };

    // Read input
    for (int i = 0; i < 9; i++) {
        scanf("%d", &clocks[i]);
    }

    // Try all possible combinations of moves
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            for (int c = 0; c < 4; c++) {
                for (int d = 0; d < 4; d++) {
                    for (int e = 0; e < 4; e++) {
                        for (int f = 0; f < 4; f++) {
                            for (int g = 0; g < 4; g++) {
                                for (int h = 0; h < 4; h++) {
                                    for (int i = 0; i < 4; i++) {
                                        int new_clocks[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

                                        // Apply moves to new clocks
                                        for (int j = 0; j < 9; j++) {
                                            for (int k = 0; k < 7; k++) {
                                                if (affected[j][k] != -1) {
                                                    new_clocks[affected[j][k]] += moves[j];
                                                }
                                            }
                                        }

                                        // Check if all clocks are at 12
                                        int all_12 = 1;
                                        for (int j = 0; j < 9; j++) {
                                            if (new_clocks[j] % 4 != 0) {
                                                all_12 = 0;
                                                break;
                                            }
                                        }

                                        if (all_12) {
                                            // Output the moves in ascending order
                                            printf("%d %d %d %d %d %d %d %d %d\n",
                                                a, b, c, d, e, f, g, h, i);
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}