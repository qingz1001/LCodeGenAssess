#include <stdio.h>

int main() {
    int scores[5][4];
    int totalScores[5] = {0};
    int maxScore = 0;
    int winner = 0;

    // Read input
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &scores[i][j]);
            totalScores[i] += scores[i][j];
        }
        if (totalScores[i] > maxScore) {
            maxScore = totalScores[i];
            winner = i + 1;
        }
    }

    // Output the result
    printf("%d %d\n", winner, maxScore);

    return 0;
}