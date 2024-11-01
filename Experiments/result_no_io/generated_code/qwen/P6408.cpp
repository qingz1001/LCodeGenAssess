#include <stdio.h>

int main() {
    int scores[5][4];
    int total_scores[5] = {0};
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &scores[i][j]);
            total_scores[i] += scores[i][j];
        }
    }
    
    int max_score = total_scores[0];
    int winner = 0;
    
    for (int i = 1; i < 5; i++) {
        if (total_scores[i] > max_score) {
            max_score = total_scores[i];
            winner = i;
        }
    }
    
    printf("%d %d\n", winner + 1, max_score);
    
    return 0;
}