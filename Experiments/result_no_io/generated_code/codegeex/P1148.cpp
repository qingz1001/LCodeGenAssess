#include <stdio.h>
#include <string.h>

int main() {
    int scores[4] = {0};
    char input[100];
    int count[4];
    int heart_count[4] = {0};

    while (1) {
        // Read the count of cards for each player
        for (int i = 0; i < 4; i++) {
            if (scanf("%d", &count[i]) != 1) {
                return 0; // End of input
            }
        }

        if (count[0] == 0 && count[1] == 0 && count[2] == 0 && count[3] == 0) {
            break; // End of input
        }

        // Initialize heart_count and scores
        for (int i = 0; i < 4; i++) {
            heart_count[i] = 0;
            scores[i] = 0;
        }

        // Read each player's cards
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < count[i]; j++) {
                scanf("%s", input);
                if (input[0] == 'H') {
                    heart_count[i]++;
                } else if (strcmp(input, "S12") == 0) {
                    scores[i] -= 100;
                } else if (strcmp(input, "D11") == 0) {
                    scores[i] += 100;
                } else if (strcmp(input, "C10") == 0) {
                    scores[i] += 50;
                }
            }
        }

        // Calculate heart scores
        int full_heart_set = 0;
        int full_heart_player = -1;
        for (int i = 0; i < 4; i++) {
            if (heart_count[i] == 13) {
                full_heart_set++;
                full_heart_player = i;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (heart_count[i] == 0) {
                scores[i] -= 50;
                scores[i] -= 2;
                scores[i] -= 3;
                scores[i] -= 4;
                scores[i] -= 5;
                scores[i] -= 6;
                scores[i] -= 7;
                scores[i] -= 8;
                scores[i] -= 9;
                scores[i] -= 10;
                scores[i] -= 20;
                scores[i] -= 30;
                scores[i] -= 40;
            } else if (heart_count[i] < 13) {
                if (strcmp(input, "S12") == 0) {
                    scores[i] -= 100;
                }
                if (strcmp(input, "D11") == 0) {
                    scores[i] += 100;
                }
                scores[i] -= 50;
                scores[i] -= 2 * (13 - heart_count[i]);
            } else if (heart_count[i] == 13) {
                if (strcmp(input, "S12") == 0) {
                    scores[i] += 100;
                }
                if (strcmp(input, "D11") == 0) {
                    scores[i] += 100;
                }
                scores[i] += 200;
            }
        }

        // Check for C10 special condition
        for (int i = 0; i < 4; i++) {
            if (count[i] == 1 && strcmp(input, "C10") == 0) {
                scores[i] += 50;
            } else if (strcmp(input, "C10") == 0) {
                scores[i] *= 2;
            }
        }

        // Check for full heart set
        if (full_heart_set == 1) {
            scores[full_heart_player] += 200;
            if (heart_count[full_heart_player] == 13) {
                scores[full_heart_player] += 500;
            }
        }

        // Output scores
        for (int i = 0; i < 4; i++) {
            if (scores[i] > 0) {
                printf("+%d ", scores[i]);
            } else {
                printf("%d ", scores[i]);
            }
        }
        printf("\n");
    }

    return 0;
}