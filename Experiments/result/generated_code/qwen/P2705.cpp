#include <stdio.h>

int main() {
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);

    int max_score = 0;

    // Calculate the maximum score by placing red balls in red boxes and blue balls in blue boxes
    int score1 = R * C + B * D;

    // Calculate the maximum score by placing all red balls in blue boxes and all blue balls in red boxes
    int score2 = R * E + B * E;

    // The maximum score is the greater of the two calculated scores
    if (score1 > score2) {
        max_score = score1;
    } else {
        max_score = score2;
    }

    printf("%d\n", max_score);

    return 0;
}